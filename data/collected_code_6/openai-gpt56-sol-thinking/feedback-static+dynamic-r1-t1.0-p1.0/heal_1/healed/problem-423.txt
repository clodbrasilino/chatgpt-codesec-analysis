#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static bool read_nonspace(int *character)
{
    int value;

    if (character == NULL) {
        return false;
    }

    do {
        value = fgetc(stdin);
    } while (value != EOF && isspace((unsigned char)value));

    if (value == EOF) {
        return false;
    }

    *character = value;
    return true;
}

static bool valid_token_end(int character)
{
    if (character == EOF) {
        return !ferror(stdin);
    }

    return isspace((unsigned char)character) != 0;
}

static bool read_size_value(size_t *result)
{
    size_t value = 0;
    int character;

    if (result == NULL || !read_nonspace(&character)) {
        return false;
    }

    if (character == '+') {
        character = fgetc(stdin);
    } else if (character == '-') {
        return false;
    }

    if (character < '0' || character > '9') {
        return false;
    }

    do {
        size_t digit = (size_t)(character - '0');

        if (value > (SIZE_MAX - digit) / 10) {
            return false;
        }

        value = value * 10 + digit;
        character = fgetc(stdin);
    } while (character >= '0' && character <= '9');

    if (!valid_token_end(character)) {
        return false;
    }

    *result = value;
    return true;
}

static bool read_int64_value(int64_t *result)
{
    uint64_t value = 0;
    uint64_t limit;
    bool negative = false;
    int character;

    if (result == NULL || !read_nonspace(&character)) {
        return false;
    }

    if (character == '+' || character == '-') {
        negative = character == '-';
        character = fgetc(stdin);
    }

    if (character < '0' || character > '9') {
        return false;
    }

    limit = negative
                ? (uint64_t)INT64_MAX + UINT64_C(1)
                : (uint64_t)INT64_MAX;

    do {
        uint64_t digit = (uint64_t)(character - '0');

        if (value > (limit - digit) / UINT64_C(10)) {
            return false;
        }

        value = value * UINT64_C(10) + digit;
        character = fgetc(stdin);
    } while (character >= '0' && character <= '9');

    if (!valid_token_end(character)) {
        return false;
    }

    if (negative) {
        if (value == (uint64_t)INT64_MAX + UINT64_C(1)) {
            *result = INT64_MIN;
        } else {
            *result = -(int64_t)value;
        }
    } else {
        *result = (int64_t)value;
    }

    return true;
}

static bool checked_add_int64(int64_t a, int64_t b, int64_t *result)
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

            if (row + 1 < rows && previous[row + 1] > best) {
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
    size_t rows;
    size_t columns;
    size_t element_count;
    int64_t *mine;
    int64_t maximum_gold;

    if (!read_size_value(&rows) ||
        !read_size_value(&columns) ||
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
        if (!read_int64_value(&mine[index])) {
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