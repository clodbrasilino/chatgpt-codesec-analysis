#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    GOLD_OK,
    GOLD_INVALID_ARGUMENT,
    GOLD_ALLOCATION_FAILURE,
    GOLD_ARITHMETIC_OVERFLOW
} GoldStatus;

typedef struct {
    FILE *stream;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char buffer[4096];
    size_t position;
    size_t length;
    bool end_of_input;
    bool io_error;
} InputReader;

static int input_get_character(InputReader *reader)
{
    if (reader == NULL) {
        return EOF;
    }

    if (reader->stream == NULL) {
        reader->io_error = true;
        reader->end_of_input = true;
        return EOF;
    }

    if (reader->io_error || reader->end_of_input) {
        return EOF;
    }

    if (reader->position == reader->length) {
        reader->position = 0;
        reader->length = fread(reader->buffer,
                               sizeof(reader->buffer[0]),
                               sizeof(reader->buffer),
                               reader->stream);

        if (ferror(reader->stream) != 0) {
            reader->length = 0;
            reader->io_error = true;
            reader->end_of_input = true;
            return EOF;
        }

        if (reader->length == 0) {
            reader->end_of_input = true;
            return EOF;
        }
    }

    return (int)reader->buffer[reader->position++];
}

static int read_non_whitespace(InputReader *reader)
{
    int character;

    do {
        character = input_get_character(reader);
    } while (character != EOF &&
             isspace((unsigned char)character) != 0);

    return character;
}

static bool read_size_value(InputReader *reader, size_t *value)
{
    int character;
    size_t result = 0;

    if (reader == NULL ||
        value == NULL ||
        reader->stream == NULL ||
        reader->io_error) {
        return false;
    }

    character = read_non_whitespace(reader);

    if (character == '+') {
        character = input_get_character(reader);
    } else if (character == '-') {
        return false;
    }

    if (character < '0' || character > '9') {
        return false;
    }

    do {
        size_t digit = (size_t)(character - '0');

        if (result > (SIZE_MAX - digit) / (size_t)10) {
            return false;
        }

        result = result * (size_t)10 + digit;
        character = input_get_character(reader);
    } while (character >= '0' && character <= '9');

    if (character != EOF &&
        isspace((unsigned char)character) == 0) {
        return false;
    }

    if (reader->io_error) {
        return false;
    }

    *value = result;
    return true;
}

static bool read_int64_value(InputReader *reader, int64_t *value)
{
    int character;
    bool negative = false;
    uint64_t magnitude = 0;
    uint64_t limit;

    if (reader == NULL ||
        value == NULL ||
        reader->stream == NULL ||
        reader->io_error) {
        return false;
    }

    character = read_non_whitespace(reader);

    if (character == '+' || character == '-') {
        negative = character == '-';
        character = input_get_character(reader);
    }

    if (character < '0' || character > '9') {
        return false;
    }

    limit = negative
        ? (uint64_t)INT64_MAX + UINT64_C(1)
        : (uint64_t)INT64_MAX;

    do {
        uint64_t digit = (uint64_t)(character - '0');

        if (magnitude > (limit - digit) / UINT64_C(10)) {
            return false;
        }

        magnitude = magnitude * UINT64_C(10) + digit;
        character = input_get_character(reader);
    } while (character >= '0' && character <= '9');

    if (character != EOF &&
        isspace((unsigned char)character) == 0) {
        return false;
    }

    if (reader->io_error) {
        return false;
    }

    if (negative) {
        if (magnitude == (uint64_t)INT64_MAX + UINT64_C(1)) {
            *value = INT64_MIN;
        } else {
            *value = -(int64_t)magnitude;
        }
    } else {
        *value = (int64_t)magnitude;
    }

    return true;
}

static bool input_has_only_whitespace(InputReader *reader)
{
    int character;

    if (reader == NULL ||
        reader->stream == NULL ||
        reader->io_error) {
        return false;
    }

    while ((character = input_get_character(reader)) != EOF) {
        if (isspace((unsigned char)character) == 0) {
            return false;
        }
    }

    return !reader->io_error;
}

static bool add_int64_checked(int64_t left, int64_t right, int64_t *result)
{
    if (result == NULL) {
        return false;
    }

    if (right > 0 && left > INT64_MAX - right) {
        return false;
    }

    if (right < 0 && left < INT64_MIN - right) {
        return false;
    }

    *result = left + right;
    return true;
}

GoldStatus solve_gold_mine(const int64_t *mine,
                           size_t rows,
                           size_t columns,
                           int64_t *maximum_gold)
{
    size_t cell_count;
    int64_t *previous;
    int64_t *current = NULL;

    if (mine == NULL ||
        maximum_gold == NULL ||
        rows == 0 ||
        columns == 0) {
        return GOLD_INVALID_ARGUMENT;
    }

    if (rows > SIZE_MAX / columns) {
        return GOLD_INVALID_ARGUMENT;
    }

    cell_count = rows * columns;

    if (cell_count > SIZE_MAX / sizeof(*mine) ||
        rows > SIZE_MAX / sizeof(*previous)) {
        return GOLD_INVALID_ARGUMENT;
    }

    previous = malloc(rows * sizeof(*previous));
    if (previous == NULL) {
        return GOLD_ALLOCATION_FAILURE;
    }

    if (columns > 1) {
        current = malloc(rows * sizeof(*current));
        if (current == NULL) {
            free(previous);
            return GOLD_ALLOCATION_FAILURE;
        }
    }

    for (size_t row = 0; row < rows; ++row) {
        previous[row] = mine[row * columns];
    }

    for (size_t column = 1; column < columns; ++column) {
        for (size_t row = 0; row < rows; ++row) {
            int64_t best = previous[row];

            if (row > 0 && previous[row - 1] > best) {
                best = previous[row - 1];
            }

            if (row + 1 < rows && previous[row + 1] > best) {
                best = previous[row + 1];
            }

            if (!add_int64_checked(best,
                                   mine[row * columns + column],
                                   &current[row])) {
                free(current);
                free(previous);
                return GOLD_ARITHMETIC_OVERFLOW;
            }
        }

        {
            int64_t *temporary = previous;
            previous = current;
            current = temporary;
        }
    }

    *maximum_gold = previous[0];

    for (size_t row = 1; row < rows; ++row) {
        if (previous[row] > *maximum_gold) {
            *maximum_gold = previous[row];
        }
    }

    free(current);
    free(previous);

    return GOLD_OK;
}

int main(void)
{
    InputReader input = {
        .stream = stdin,
        .buffer = {0},
        .position = 0,
        .length = 0,
        .end_of_input = false,
        .io_error = false
    };
    size_t rows;
    size_t columns;
    size_t cell_count;
    int64_t *mine;
    int64_t maximum_gold;
    GoldStatus status;

    if (!read_size_value(&input, &rows) ||
        !read_size_value(&input, &columns) ||
        rows == 0 ||
        columns == 0) {
        fputs(input.io_error ? "Input error\n" : "Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (rows > SIZE_MAX / columns) {
        fputs("Matrix dimensions are too large\n", stderr);
        return EXIT_FAILURE;
    }

    cell_count = rows * columns;

    if (cell_count > SIZE_MAX / sizeof(*mine)) {
        fputs("Matrix dimensions are too large\n", stderr);
        return EXIT_FAILURE;
    }

    mine = malloc(cell_count * sizeof(*mine));
    if (mine == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t index = 0; index < cell_count; ++index) {
        if (!read_int64_value(&input, &mine[index])) {
            fputs(input.io_error
                      ? "Input error\n"
                      : "Invalid matrix data\n",
                  stderr);
            free(mine);
            return EXIT_FAILURE;
        }
    }

    if (!input_has_only_whitespace(&input)) {
        fputs(input.io_error
                  ? "Input error\n"
                  : "Invalid matrix data\n",
              stderr);
        free(mine);
        return EXIT_FAILURE;
    }

    status = solve_gold_mine(mine, rows, columns, &maximum_gold);
    free(mine);

    switch (status) {
        case GOLD_OK:
            if (printf("%" PRId64 "\n", maximum_gold) < 0 ||
                fflush(stdout) == EOF) {
                fputs("Output error\n", stderr);
                return EXIT_FAILURE;
            }
            return EXIT_SUCCESS;

        case GOLD_ALLOCATION_FAILURE:
            fputs("Memory allocation failed\n", stderr);
            break;

        case GOLD_ARITHMETIC_OVERFLOW:
            fputs("Arithmetic overflow\n", stderr);
            break;

        case GOLD_INVALID_ARGUMENT:
        default:
            fputs("Invalid argument\n", stderr);
            break;
    }

    return EXIT_FAILURE;
}