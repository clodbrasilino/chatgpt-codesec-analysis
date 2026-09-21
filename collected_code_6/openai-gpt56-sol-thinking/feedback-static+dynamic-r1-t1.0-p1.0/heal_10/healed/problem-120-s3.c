#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

enum {
    INPUT_BUFFER_SIZE = 4096
};

typedef struct {
    int64_t first;
    int64_t second;
} Tuple;

typedef struct {
    FILE *stream;
    unsigned char *buffer;
    size_t capacity;
    size_t position;
    size_t length;
    bool end_after_buffer;
    bool error_after_buffer;
    bool end_of_file;
    bool error;
} InputScanner;

static bool scanner_init(InputScanner *scanner, FILE *stream)
{
    if (scanner == NULL || stream == NULL) {
        return false;
    }

    scanner->buffer = malloc(INPUT_BUFFER_SIZE);
    if (scanner->buffer == NULL) {
        return false;
    }

    scanner->stream = stream;
    scanner->capacity = INPUT_BUFFER_SIZE;
    scanner->position = 0;
    scanner->length = 0;
    scanner->end_after_buffer = false;
    scanner->error_after_buffer = false;
    scanner->end_of_file = false;
    scanner->error = false;

    return true;
}

static void scanner_destroy(InputScanner *scanner)
{
    if (scanner == NULL) {
        return;
    }

    free(scanner->buffer);
    scanner->buffer = NULL;
    scanner->capacity = 0;
    scanner->position = 0;
    scanner->length = 0;
}

static bool scanner_get(InputScanner *scanner, int *character)
{
    if (scanner == NULL || character == NULL || scanner->stream == NULL ||
        scanner->buffer == NULL || scanner->capacity == 0 ||
        scanner->end_of_file || scanner->error) {
        return false;
    }

    if (scanner->position >= scanner->length) {
        size_t bytes_read;

        scanner->position = 0;
        scanner->length = 0;

        if (scanner->error_after_buffer) {
            scanner->error = true;
            return false;
        }

        if (scanner->end_after_buffer) {
            scanner->end_of_file = true;
            return false;
        }

        bytes_read = fread(scanner->buffer, 1, scanner->capacity,
                           scanner->stream);

        if (bytes_read == 0) {
            if (ferror(scanner->stream)) {
                scanner->error = true;
            } else {
                scanner->end_of_file = true;
            }
            return false;
        }

        scanner->length = bytes_read;

        if (bytes_read < scanner->capacity) {
            if (ferror(scanner->stream)) {
                scanner->error_after_buffer = true;
            } else if (feof(scanner->stream)) {
                scanner->end_after_buffer = true;
            }
        }
    }

    *character = (int)scanner->buffer[scanner->position++];
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

int main(void)
{
    InputScanner scanner;
    size_t count;
    int64_t maximum_product = INT64_MIN;
    int status = EXIT_FAILURE;

    if (!scanner_init(&scanner, stdin)) {
        fprintf(stderr, "Unable to initialize input scanner\n");
        return EXIT_FAILURE;
    }

    if (!read_size_value(&scanner, &count) || count == 0) {
        fprintf(stderr, "Invalid tuple count\n");
        goto cleanup;
    }

    for (size_t index = 0; index < count; ++index) {
        Tuple tuple;
        int64_t product;

        if (!read_int64_value(&scanner, &tuple.first) ||
            !read_int64_value(&scanner, &tuple.second)) {
            fprintf(stderr, "Invalid tuple input\n");
            goto cleanup;
        }

        if (!multiply_checked(tuple.first, tuple.second, &product)) {
            fprintf(stderr, "Tuple product is outside the int64_t range\n");
            goto cleanup;
        }

        if (product > maximum_product) {
            maximum_product = product;
        }
    }

    if (printf("%" PRId64 "\n", maximum_product) < 0) {
        fprintf(stderr, "Output error\n");
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    scanner_destroy(&scanner);
    return status;
}