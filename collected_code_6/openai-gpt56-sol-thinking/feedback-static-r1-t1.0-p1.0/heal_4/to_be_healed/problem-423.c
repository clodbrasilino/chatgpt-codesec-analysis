#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct {
    FILE *stream;
} input_reader;

static bool input_reader_init(input_reader *reader, FILE *stream)
{
    if (reader == NULL || stream == NULL) {
        return false;
    }

    reader->stream = stream;
    return true;
}

static int input_reader_get(input_reader *reader, int *character)
{
    int value;

    if (reader == NULL || reader->stream == NULL || character == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    value = fgetc(reader->stream);
    if (value == EOF) {
        return ferror(reader->stream) ? -1 : 0;
    }

    *character = value;
    return 1;
}

static bool read_non_space(input_reader *reader, int *character)
{
    if (reader == NULL || character == NULL) {
        return false;
    }

    for (;;) {
        int status = input_reader_get(reader, character);

        if (status != 1) {
            return false;
        }

        if (!isspace((unsigned char)*character)) {
            return true;
        }
    }
}

static bool read_size(input_reader *reader, size_t *result)
{
    int character;
    size_t value = 0;

    if (reader == NULL || result == NULL ||
        !read_non_space(reader, &character)) {
        return false;
    }

    if (character == '+') {
        if (input_reader_get(reader, &character) != 1) {
            return false;
        }
    } else if (character == '-') {
        return false;
    }

    if (character < '0' || character > '9') {
        return false;
    }

    for (;;) {
        size_t digit = (size_t)(character - '0');
        int status;

        if (value > (SIZE_MAX - digit) / 10U) {
            return false;
        }

        value = value * 10U + digit;
        status = input_reader_get(reader, &character);

        if (status == 0) {
            break;
        }

        if (status < 0) {
            return false;
        }

        if (character < '0' || character > '9') {
            if (!isspace((unsigned char)character)) {
                return false;
            }
            break;
        }
    }

    *result = value;
    return true;
}

static bool read_int64(input_reader *reader, int64_t *result)
{
    int character;
    bool negative = false;
    uint64_t magnitude = 0;
    uint64_t limit;

    if (reader == NULL || result == NULL ||
        !read_non_space(reader, &character)) {
        return false;
    }

    if (character == '+' || character == '-') {
        negative = character == '-';

        if (input_reader_get(reader, &character) != 1) {
            return false;
        }
    }

    if (character < '0' || character > '9') {
        return false;
    }

    limit = negative
        ? (uint64_t)INT64_MAX + UINT64_C(1)
        : (uint64_t)INT64_MAX;

    for (;;) {
        uint64_t digit = (uint64_t)(character - '0');
        int status;

        if (magnitude > (limit - digit) / UINT64_C(10)) {
            return false;
        }

        magnitude = magnitude * UINT64_C(10) + digit;
        status = input_reader_get(reader, &character);

        if (status == 0) {
            break;
        }

        if (status < 0) {
            return false;
        }

        if (character < '0' || character > '9') {
            if (!isspace((unsigned char)character)) {
                return false;
            }
            break;
        }
    }

    if (negative) {
        if (magnitude == (uint64_t)INT64_MAX + UINT64_C(1)) {
            *result = INT64_MIN;
        } else {
            *result = -(int64_t)magnitude;
        }
    } else {
        *result = (int64_t)magnitude;
    }

    return true;
}

static bool checked_add_int64(int64_t left, int64_t right, int64_t *result)
{
    if (result == NULL) {
        return false;
    }

    if ((right > 0 && left > INT64_MAX - right) ||
        (right < 0 && left < INT64_MIN - right)) {
        return false;
    }

    *result = left + right;
    return true;
}

static bool gold_mine_max(const int64_t *mine, size_t rows, size_t columns,
                          int64_t *result)
{
    int64_t *previous;
    int64_t *current;

    if (mine == NULL || result == NULL || rows == 0 || columns == 0) {
        return false;
    }

    if (rows > SIZE_MAX / columns ||
        rows > SIZE_MAX / sizeof(*previous)) {
        return false;
    }

    previous = malloc(rows * sizeof(*previous));
    current = malloc(rows * sizeof(*current));

    if (previous == NULL || current == NULL) {
        free(previous);
        free(current);
        return false;
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

            if (row < rows - 1 && previous[row + 1] > best) {
                best = previous[row + 1];
            }

            if (!checked_add_int64(best, mine[row * columns + column],
                                   &current[row])) {
                free(previous);
                free(current);
                return false;
            }
        }

        {
            int64_t *temporary = previous;
            previous = current;
            current = temporary;
        }
    }

    *result = previous[0];

    for (size_t row = 1; row < rows; ++row) {
        if (previous[row] > *result) {
            *result = previous[row];
        }
    }

    free(previous);
    free(current);
    return true;
}

int main(void)
{
    input_reader reader;
    size_t rows;
    size_t columns;
    size_t element_count;
    int64_t *mine;
    int64_t maximum_gold;

    if (!input_reader_init(&reader, stdin)) {
        return EXIT_FAILURE;
    }

    if (!read_size(&reader, &rows) ||
        !read_size(&reader, &columns) ||
        rows == 0 ||
        columns == 0) {
        return EXIT_FAILURE;
    }

    if (rows > SIZE_MAX / columns) {
        return EXIT_FAILURE;
    }

    element_count = rows * columns;

    if (element_count > SIZE_MAX / sizeof(*mine)) {
        return EXIT_FAILURE;
    }

    mine = malloc(element_count * sizeof(*mine));
    if (mine == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t index = 0; index < element_count; ++index) {
        if (!read_int64(&reader, &mine[index])) {
            free(mine);
            return EXIT_FAILURE;
        }
    }

    if (!gold_mine_max(mine, rows, columns, &maximum_gold)) {
        free(mine);
        return EXIT_FAILURE;
    }

    free(mine);

    if (printf("%" PRId64 "\n", maximum_gold) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}