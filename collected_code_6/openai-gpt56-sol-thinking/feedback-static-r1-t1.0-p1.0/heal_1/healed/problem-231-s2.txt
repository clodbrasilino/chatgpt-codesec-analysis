#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stddef.h>
#include <limits.h>
#include <ctype.h>

static bool calculate_triangular_number(size_t value, size_t *result)
{
    size_t first;
    size_t second;

    if (result == NULL || value == SIZE_MAX) {
        return false;
    }

    first = value;
    second = value + 1;

    if ((first & 1U) == 0U) {
        first /= 2;
    } else {
        second /= 2;
    }

    if (second != 0 && first > SIZE_MAX / second) {
        return false;
    }

    *result = first * second;
    return true;
}

static bool calculate_element_count(size_t rows, size_t *count)
{
    if (rows == 0) {
        return false;
    }

    return calculate_triangular_number(rows, count);
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

static bool token_ended_validly(int character)
{
    if (character == EOF) {
        return ferror(stdin) == 0;
    }

    return isspace((unsigned char)character) != 0;
}

static bool read_size_value(size_t *result)
{
    size_t value = 0;
    int character;

    if (result == NULL) {
        return false;
    }

    do {
        character = fgetc(stdin);
    } while (character != EOF &&
             isspace((unsigned char)character) != 0);

    if (character == EOF) {
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
        unsigned int digit = (unsigned int)(character - '0');

        if (value > (SIZE_MAX - digit) / 10U) {
            return false;
        }

        value = value * 10U + digit;
        character = fgetc(stdin);
    } while (character >= '0' && character <= '9');

    if (!token_ended_validly(character)) {
        return false;
    }

    *result = value;
    return true;
}

static bool read_int64_value(int64_t *result)
{
    uint64_t magnitude = 0;
    uint64_t limit;
    bool negative = false;
    int character;

    if (result == NULL) {
        return false;
    }

    do {
        character = fgetc(stdin);
    } while (character != EOF &&
             isspace((unsigned char)character) != 0);

    if (character == EOF) {
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

        if (magnitude > (limit - digit) / UINT64_C(10)) {
            return false;
        }

        magnitude = magnitude * UINT64_C(10) + digit;
        character = fgetc(stdin);
    } while (character >= '0' && character <= '9');

    if (!token_ended_validly(character)) {
        return false;
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

static bool input_has_only_trailing_whitespace(void)
{
    int character;

    while ((character = fgetc(stdin)) != EOF) {
        if (isspace((unsigned char)character) == 0) {
            return false;
        }
    }

    return ferror(stdin) == 0;
}

static bool find_max_sum(const int64_t *triangle,
                         size_t rows,
                         int64_t *result)
{
    int64_t *sums;
    size_t element_count;
    size_t last_row_offset;

    if (triangle == NULL || result == NULL ||
        !calculate_element_count(rows, &element_count) ||
        rows > SIZE_MAX / sizeof(*sums)) {
        return false;
    }

    sums = malloc(rows * sizeof(*sums));
    if (sums == NULL) {
        return false;
    }

    last_row_offset = element_count - rows;

    for (size_t column = 0; column < rows; ++column) {
        sums[column] = triangle[last_row_offset + column];
    }

    for (size_t row = rows - 1; row-- > 0;) {
        size_t row_offset;

        if (!calculate_triangular_number(row, &row_offset)) {
            free(sums);
            return false;
        }

        for (size_t column = 0; column <= row; ++column) {
            int64_t child = sums[column] > sums[column + 1]
                                ? sums[column]
                                : sums[column + 1];

            if (!checked_add_int64(triangle[row_offset + column],
                                   child,
                                   &sums[column])) {
                free(sums);
                return false;
            }
        }
    }

    *result = sums[0];
    free(sums);
    return true;
}

int main(void)
{
    size_t rows;
    size_t element_count;
    int64_t *triangle;
    int64_t maximum_sum;

    if (!read_size_value(&rows) ||
        !calculate_element_count(rows, &element_count) ||
        element_count > SIZE_MAX / sizeof(*triangle)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    triangle = malloc(element_count * sizeof(*triangle));
    if (triangle == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t index = 0; index < element_count; ++index) {
        if (!read_int64_value(&triangle[index])) {
            fputs("Invalid input\n", stderr);
            free(triangle);
            return EXIT_FAILURE;
        }
    }

    if (!input_has_only_trailing_whitespace()) {
        fputs("Invalid input\n", stderr);
        free(triangle);
        return EXIT_FAILURE;
    }

    if (!find_max_sum(triangle, rows, &maximum_sum)) {
        fputs("Unable to calculate maximum sum\n", stderr);
        free(triangle);
        return EXIT_FAILURE;
    }

    printf("%" PRId64 "\n", maximum_sum);
    free(triangle);
    return EXIT_SUCCESS;
}