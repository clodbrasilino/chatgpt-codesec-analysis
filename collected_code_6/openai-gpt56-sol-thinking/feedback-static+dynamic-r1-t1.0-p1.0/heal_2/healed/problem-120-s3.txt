#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct {
    int64_t first;
    int64_t second;
} Tuple;

static bool read_nonspace_character(int *character)
{
    int current;

    if (character == NULL) {
        return false;
    }

    do {
        current = fgetc(stdin);
    } while (current != EOF && isspace((unsigned char)current));

    if (current == EOF) {
        return false;
    }

    *character = current;
    return true;
}

static bool read_size_value(size_t *value)
{
    int character;
    uintmax_t parsed = 0;
    const uintmax_t limit = (uintmax_t)SIZE_MAX;
    bool has_digit = false;
    bool valid = true;
    bool overflow = false;

    if (value == NULL || !read_nonspace_character(&character)) {
        return false;
    }

    if (character == '+' || character == '-') {
        if (character == '-') {
            valid = false;
        }
        character = fgetc(stdin);
    }

    while (character != EOF && !isspace((unsigned char)character)) {
        if (character >= '0' && character <= '9') {
            uintmax_t digit = (uintmax_t)(character - '0');

            has_digit = true;

            if (!overflow) {
                if (parsed > (limit - digit) / UINTMAX_C(10)) {
                    overflow = true;
                } else {
                    parsed = parsed * UINTMAX_C(10) + digit;
                }
            }
        } else {
            valid = false;
        }

        character = fgetc(stdin);
    }

    if (character == EOF && ferror(stdin)) {
        return false;
    }

    if (!valid || !has_digit || overflow) {
        return false;
    }

    *value = (size_t)parsed;
    return true;
}

static bool read_int64_value(int64_t *value)
{
    int character;
    uintmax_t parsed = 0;
    uintmax_t limit;
    bool negative = false;
    bool has_digit = false;
    bool valid = true;
    bool overflow = false;

    if (value == NULL || !read_nonspace_character(&character)) {
        return false;
    }

    if (character == '+' || character == '-') {
        negative = character == '-';
        character = fgetc(stdin);
    }

    limit = negative
        ? (uintmax_t)INT64_MAX + UINTMAX_C(1)
        : (uintmax_t)INT64_MAX;

    while (character != EOF && !isspace((unsigned char)character)) {
        if (character >= '0' && character <= '9') {
            uintmax_t digit = (uintmax_t)(character - '0');

            has_digit = true;

            if (!overflow) {
                if (parsed > (limit - digit) / UINTMAX_C(10)) {
                    overflow = true;
                } else {
                    parsed = parsed * UINTMAX_C(10) + digit;
                }
            }
        } else {
            valid = false;
        }

        character = fgetc(stdin);
    }

    if (character == EOF && ferror(stdin)) {
        return false;
    }

    if (!valid || !has_digit || overflow) {
        return false;
    }

    if (negative) {
        if (parsed == (uintmax_t)INT64_MAX + UINTMAX_C(1)) {
            *value = INT64_MIN;
        } else {
            *value = -(int64_t)parsed;
        }
    } else {
        *value = (int64_t)parsed;
    }

    return true;
}

static bool multiply_checked(int64_t left, int64_t right, int64_t *result)
{
    if (result == NULL) {
        return false;
    }

    if (left > 0) {
        if ((right > 0 && left > INT64_MAX / right) ||
            (right < 0 && right < INT64_MIN / left)) {
            return false;
        }
    } else if (left < 0) {
        if ((right > 0 && left < INT64_MIN / right) ||
            (right < 0 && left < INT64_MAX / right)) {
            return false;
        }
    }

    *result = left * right;
    return true;
}

static bool find_maximum_tuple_product(const Tuple *tuples, size_t count,
                                       int64_t *maximum_product)
{
    int64_t maximum = INT64_MIN;

    if (tuples == NULL || maximum_product == NULL || count == 0) {
        return false;
    }

    for (size_t index = 0; index < count; ++index) {
        int64_t product;

        if (!multiply_checked(tuples[index].first, tuples[index].second,
                              &product)) {
            return false;
        }

        if (product > maximum) {
            maximum = product;
        }
    }

    *maximum_product = maximum;
    return true;
}

int main(void)
{
    size_t count;
    Tuple *tuples;
    int64_t maximum_product;

    if (!read_size_value(&count) || count == 0 ||
        count > SIZE_MAX / sizeof(*tuples)) {
        fprintf(stderr, "Invalid tuple count\n");
        return EXIT_FAILURE;
    }

    tuples = malloc(count * sizeof(*tuples));
    if (tuples == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t index = 0; index < count; ++index) {
        if (!read_int64_value(&tuples[index].first) ||
            !read_int64_value(&tuples[index].second)) {
            fprintf(stderr, "Invalid tuple input\n");
            free(tuples);
            return EXIT_FAILURE;
        }
    }

    if (!find_maximum_tuple_product(tuples, count, &maximum_product)) {
        fprintf(stderr, "Unable to calculate maximum product\n");
        free(tuples);
        return EXIT_FAILURE;
    }

    printf("%" PRId64 "\n", maximum_product);

    free(tuples);
    return EXIT_SUCCESS;
}