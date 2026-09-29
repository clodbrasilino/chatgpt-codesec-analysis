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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char buffer[4096];
    size_t position;
    size_t length;
    bool end_of_file;
    bool error;
} InputScanner;

static bool scanner_get(InputScanner *scanner, int *character)
{
    if (scanner == NULL || character == NULL || scanner->stream == NULL) {
        return false;
    }

    if (scanner->position == scanner->length) {
        if (scanner->end_of_file || scanner->error) {
            return false;
        }

        scanner->length = fread(scanner->buffer, 1,
                                sizeof(scanner->buffer), scanner->stream);
        scanner->position = 0;

        if (scanner->length == 0) {
            if (ferror(scanner->stream)) {
                scanner->error = true;
            } else {
                scanner->end_of_file = true;
            }
            return false;
        }
    }

    *character = scanner->buffer[scanner->position++];
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

static bool multiply_checked(int64_t left, int64_t right, int64_t *result)
{
    if (result == NULL) {
        return false;
    }

    if (left == 0 || right == 0) {
        *result = 0;
        return true;
    }

    if (left == -1 && right == INT64_MIN) {
        return false;
    }

    if (right == -1 && left == INT64_MIN) {
        return false;
    }

    if (left > 0) {
        if (right > 0) {
            if (left > INT64_MAX / right) {
                return false;
            }
        } else if (right < INT64_MIN / left) {
            return false;
        }
    } else {
        /* Possible weaknesses found:
         *  Assuming that condition 'right>0' is not redundant
         */
        if (right > 0) {
            if (left < INT64_MIN / right) {
                return false;
            }
        /* Possible weaknesses found:
         *  Either the condition 'right>0' is redundant or there is division by zero at line 235. [zerodivcond]
         *  Division by zero
         */
        } else if (left < INT64_MAX / right) {
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
    InputScanner scanner = {
        .stream = stdin,
        .position = 0,
        .length = 0,
        .end_of_file = false,
        .error = false
    };
    size_t count;
    Tuple *tuples;
    int64_t maximum_product;

    if (!read_size_value(&scanner, &count) ||
        count == 0 ||
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