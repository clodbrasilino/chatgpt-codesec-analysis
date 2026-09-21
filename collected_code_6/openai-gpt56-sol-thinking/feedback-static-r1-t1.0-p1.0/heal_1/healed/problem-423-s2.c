#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    GOLD_OK,
    GOLD_INVALID_ARGUMENT,
    GOLD_ALLOCATION_FAILURE,
    GOLD_ARITHMETIC_OVERFLOW
} GoldStatus;

static bool read_token(FILE *stream, char *buffer, size_t capacity)
{
    int character;
    size_t length = 0;
    bool fits = true;

    if (stream == NULL || buffer == NULL || capacity < 2) {
        return false;
    }

    do {
        character = fgetc(stream);
    } while (character != EOF && isspace((unsigned char)character));

    if (character == EOF) {
        return false;
    }

    do {
        if (length < capacity - 1) {
            buffer[length++] = (char)character;
        } else {
            fits = false;
        }

        character = fgetc(stream);
    } while (character != EOF && !isspace((unsigned char)character));

    buffer[length] = '\0';
    return fits;
}

static bool read_size_value(FILE *stream, size_t *value)
{
    char token[128];
    char *end;
    uintmax_t parsed;

    if (value == NULL || !read_token(stream, token, sizeof(token))) {
        return false;
    }

    if (token[0] == '\0' || token[0] == '-') {
        return false;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed > (uintmax_t)SIZE_MAX) {
        return false;
    }

    *value = (size_t)parsed;
    return true;
}

static bool read_int64_value(FILE *stream, int64_t *value)
{
    char token[128];
    char *end;
    intmax_t parsed;

    if (value == NULL || !read_token(stream, token, sizeof(token))) {
        return false;
    }

    errno = 0;
    end = NULL;
    parsed = strtoimax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return false;
    }

    *value = (int64_t)parsed;
    return true;
}

static bool add_int64_checked(int64_t a, int64_t b, int64_t *result)
{
    if (result == NULL) {
        return false;
    }

    if ((b > 0 && a > INT64_MAX - b) ||
        (b < 0 && a < INT64_MIN - b)) {
        return false;
    }

    *result = a + b;
    return true;
}

GoldStatus solve_gold_mine(const int64_t *mine,
                           size_t rows,
                           size_t columns,
                           int64_t *maximum_gold)
{
    int64_t *previous;
    int64_t *current;
    int64_t *temporary;

    if (mine == NULL || maximum_gold == NULL ||
        rows == 0 || columns == 0) {
        return GOLD_INVALID_ARGUMENT;
    }

    if (rows > SIZE_MAX / columns ||
        rows > SIZE_MAX / sizeof(*previous)) {
        return GOLD_INVALID_ARGUMENT;
    }

    previous = malloc(rows * sizeof(*previous));
    if (previous == NULL) {
        return GOLD_ALLOCATION_FAILURE;
    }

    current = malloc(rows * sizeof(*current));
    if (current == NULL) {
        free(previous);
        return GOLD_ALLOCATION_FAILURE;
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

        temporary = previous;
        previous = current;
        current = temporary;
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
    size_t rows;
    size_t columns;
    size_t cell_count;
    int64_t *mine;
    int64_t maximum_gold;
    GoldStatus status;

    if (!read_size_value(stdin, &rows) ||
        !read_size_value(stdin, &columns) ||
        rows == 0 || columns == 0) {
        fputs("Invalid input\n", stderr);
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
        if (!read_int64_value(stdin, &mine[index])) {
            fputs("Invalid matrix data\n", stderr);
            free(mine);
            return EXIT_FAILURE;
        }
    }

    status = solve_gold_mine(mine, rows, columns, &maximum_gold);
    free(mine);

    switch (status) {
        case GOLD_OK:
            printf("%" PRId64 "\n", maximum_gold);
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