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

typedef struct {
    FILE *stream;
    bool end_of_file;
    bool error;
} InputScanner;

static bool scanner_get(InputScanner *scanner, int *character)
{
    int current;

    if (scanner == NULL || character == NULL || scanner->stream == NULL ||
        scanner->end_of_file || scanner->error) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    current = fgetc(scanner->stream);

    if (current == EOF) {
        if (ferror(scanner->stream)) {
            scanner->error = true;
        } else {
            scanner->end_of_file = true;
        }
        return false;
    }

    *character = current;
    return true;
}

static bool read_nonspace_character(InputScanner *scanner, int *character)
{
    int current;

    if (scanner == NULL || character == NULL) {
        return false;
    }

    while (scanner_get(scanner, &current)) {
        if (!isspace((unsigned char)current)) {
            *character = current;
            return true;
        }
    }

    return false;
}

static bool read_size_value(InputScanner *scanner, size_t *value)
{
    int character;
    uintmax_t parsed = 0;
    const uintmax_t limit = (uintmax_t)SIZE_MAX;
    bool has_digit = false;
    bool valid = true;
    bool overflow = false;

    if (scanner == NULL || value == NULL ||
        !read_nonspace_character(scanner, &character)) {
        return false;
    }

    if (character == '+' || character == '-') {
        if (character == '-') {
            valid = false;
        }

        if (!scanner_get(scanner, &character)) {
            return false;
        }
    }

    for (;;) {
        if (isspace((unsigned char)character)) {
            break;
        }

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

        if (!scanner_get(scanner, &character)) {
            if (scanner->error) {
                return false;
            }
            break;
        }
    }

    if (!valid || !has_digit || overflow) {
        return false;
    }

    *value = (size_t)parsed;
    return true;
}

static bool read_int64_value(InputScanner *scanner, int64_t *value)
{
    int character;
    uintmax_t parsed = 0;
    uintmax_t limit;
    bool negative = false;
    bool has_digit = false;
    bool valid = true;
    bool overflow = false;

    if (scanner == NULL || value == NULL ||
        !read_nonspace_character(scanner, &character)) {
        return false;
    }

    if (character == '+' || character == '-') {
        negative = character == '-';

        if (!scanner_get(scanner, &character)) {
            return false;
        }
    }

    limit = negative
        ? (uintmax_t)INT64_MAX + UINTMAX_C(1)
        : (uintmax_t)INT64_MAX;

    for (;;) {
        if (isspace((unsigned char)character)) {
            break;
        }

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

        if (!scanner_get(scanner, &character)) {
            if (scanner->error) {
                return false;
            }
            break;
        }
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

static uint64_t int64_magnitude(int64_t value)
{
    if (value >= 0) {
        return (uint64_t)value;
    }

    return (uint64_t)(-(value + INT64_C(1))) + UINT64_C(1);
}

static bool multiply_checked(int64_t left, int64_t right, int64_t *result)
{
    uint64_t left_magnitude;
    uint64_t right_magnitude;
    uint64_t product_magnitude;
    uint64_t limit;
    bool negative;

    if (result == NULL) {
        return false;
    }

    if (left == 0 || right == 0) {
        *result = 0;
        return true;
    }

    negative = (left < 0) != (right < 0);
    left_magnitude = int64_magnitude(left);
    right_magnitude = int64_magnitude(right);
    limit = negative
        ? (uint64_t)INT64_MAX + UINT64_C(1)
        : (uint64_t)INT64_MAX;

    if (left_magnitude > limit / right_magnitude) {
        return false;
    }

    product_magnitude = left_magnitude * right_magnitude;

    if (negative) {
        if (product_magnitude ==
            (uint64_t)INT64_MAX + UINT64_C(1)) {
            *result = INT64_MIN;
        } else {
            *result = -(int64_t)product_magnitude;
        }
    } else {
        *result = (int64_t)product_magnitude;
    }

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

        if (!multiply_checked(tuples[index].first,
                              tuples[index].second,
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
    InputScanner scanner = {
        .stream = stdin,
        .end_of_file = false,
        .error = false
    };
    size_t count;
    Tuple *tuples;
    int64_t maximum_product;

    if (!read_size_value(&scanner, &count) ||
        count == 0 ||
        count > SIZE_MAX / sizeof(Tuple)) {
        fprintf(stderr, "Invalid tuple count\n");
        return EXIT_FAILURE;
    }

    tuples = malloc(count * sizeof(*tuples));
    if (tuples == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t index = 0; index < count; ++index) {
        if (!read_int64_value(&scanner, &tuples[index].first) ||
            !read_int64_value(&scanner, &tuples[index].second)) {
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

    if (printf("%" PRId64 "\n", maximum_product) < 0) {
        fprintf(stderr, "Output error\n");
        free(tuples);
        return EXIT_FAILURE;
    }

    free(tuples);
    return EXIT_SUCCESS;
}