#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    FILE *stream;
    bool failed;
} Input;

static int input_get(Input *input)
{
    int character;

    if (input == NULL || input->stream == NULL) {
        return EOF;
    }

    character = fgetc(input->stream);

    if (character == EOF) {
        input->failed = ferror(input->stream) != 0;
    }

    return character;
}

static bool read_nonspace(Input *input, int *character)
{
    int value;

    if (input == NULL || character == NULL) {
        return false;
    }

    do {
        value = input_get(input);
    } while (value != EOF && isspace((unsigned char)value) != 0);

    if (value == EOF) {
        return false;
    }

    *character = value;
    return true;
}

static bool valid_token_end(const Input *input, int character)
{
    if (input == NULL) {
        return false;
    }

    if (character == EOF) {
        return !input->failed;
    }

    return isspace((unsigned char)character) != 0;
}

static bool read_size_value(Input *input, size_t *result)
{
    size_t value = 0;
    int character;

    if (input == NULL || result == NULL ||
        !read_nonspace(input, &character)) {
        return false;
    }

    if (character == '+') {
        character = input_get(input);
    } else if (character == '-') {
        return false;
    }

    if (character < '0' || character > '9') {
        return false;
    }

    do {
        size_t digit = (size_t)(character - '0');

        if (value > (SIZE_MAX - digit) / 10U) {
            return false;
        }

        value = value * 10U + digit;
        character = input_get(input);
    } while (character >= '0' && character <= '9');

    if (!valid_token_end(input, character)) {
        return false;
    }

    *result = value;
    return true;
}

static bool read_int64_value(Input *input, int64_t *result)
{
    uint64_t value = 0;
    uint64_t limit;
    bool negative = false;
    int character;

    if (input == NULL || result == NULL ||
        !read_nonspace(input, &character)) {
        return false;
    }

    if (character == '+' || character == '-') {
        negative = character == '-';
        character = input_get(input);
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
        character = input_get(input);
    } while (character >= '0' && character <= '9');

    if (!valid_token_end(input, character)) {
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
    int64_t *previous = NULL;
    int64_t *current = NULL;

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
    Input input = {stdin, false};
    size_t rows;
    size_t columns;
    size_t element_count;
    int64_t *mine = NULL;
    int64_t maximum_gold;

    if (!read_size_value(&input, &rows) ||
        !read_size_value(&input, &columns) ||
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
        if (!read_int64_value(&input, &mine[index])) {
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