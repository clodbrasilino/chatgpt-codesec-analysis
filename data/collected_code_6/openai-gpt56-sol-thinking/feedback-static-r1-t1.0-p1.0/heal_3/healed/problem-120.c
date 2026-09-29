#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int32_t first;
    int32_t second;
} Tuple;

enum {
    TOKEN_CAPACITY = 64,
    INPUT_BUFFER_CAPACITY = 4096
};

typedef struct {
    unsigned char buffer[INPUT_BUFFER_CAPACITY];
    size_t position;
    size_t length;
    bool failed;
} InputScanner;

static bool scanner_get_byte(InputScanner *scanner, unsigned char *byte)
{
    if (scanner == NULL || byte == NULL || scanner->failed) {
        return false;
    }

    if (scanner->position == scanner->length) {
        scanner->length = fread(scanner->buffer, 1,
                                sizeof(scanner->buffer), stdin);
        scanner->position = 0;

        if (scanner->length == 0) {
            if (ferror(stdin)) {
                scanner->failed = true;
            }
            return false;
        }
    }

    *byte = scanner->buffer[scanner->position++];
    return true;
}

static bool read_token(InputScanner *scanner, char *output, size_t capacity)
{
    unsigned char byte;
    size_t length = 0;
    bool found = false;
    bool valid = true;

    if (scanner == NULL || output == NULL || capacity == 0) {
        return false;
    }

    while (scanner_get_byte(scanner, &byte)) {
        if (!isspace(byte)) {
            found = true;
            break;
        }
    }

    if (!found) {
        return false;
    }

    for (;;) {
        if (byte == '\0') {
            valid = false;
        } else if (length + 1 < capacity) {
            output[length++] = (char)byte;
        } else {
            valid = false;
        }

        if (!scanner_get_byte(scanner, &byte)) {
            break;
        }

        if (isspace(byte)) {
            break;
        }
    }

    if (scanner->failed || !valid) {
        return false;
    }

    output[length] = '\0';
    return true;
}

static bool read_size_value(InputScanner *scanner, size_t *value)
{
    char buffer[TOKEN_CAPACITY];
    char *end;
    uintmax_t parsed;

    if (value == NULL ||
        !read_token(scanner, buffer, sizeof(buffer)) ||
        buffer[0] == '-') {
        return false;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE ||
        end == buffer ||
        end == NULL ||
        *end != '\0' ||
        parsed > SIZE_MAX) {
        return false;
    }

    *value = (size_t)parsed;
    return true;
}

static bool read_int32_value(InputScanner *scanner, int32_t *value)
{
    char buffer[TOKEN_CAPACITY];
    char *end;
    intmax_t parsed;

    if (value == NULL ||
        !read_token(scanner, buffer, sizeof(buffer))) {
        return false;
    }

    errno = 0;
    end = NULL;
    parsed = strtoimax(buffer, &end, 10);

    if (errno == ERANGE ||
        end == buffer ||
        end == NULL ||
        *end != '\0' ||
        parsed < INT32_MIN ||
        parsed > INT32_MAX) {
        return false;
    }

    *value = (int32_t)parsed;
    return true;
}

static bool find_maximum_product(const Tuple *tuples, size_t count,
                                 int64_t *maximum)
{
    if (tuples == NULL || maximum == NULL || count == 0) {
        return false;
    }

    *maximum = (int64_t)tuples[0].first * (int64_t)tuples[0].second;

    for (size_t i = 1; i < count; ++i) {
        int64_t product =
            (int64_t)tuples[i].first * (int64_t)tuples[i].second;

        if (product > *maximum) {
            *maximum = product;
        }
    }

    return true;
}

int main(void)
{
    InputScanner scanner = { { 0 }, 0, 0, false };
    size_t count;
    Tuple *tuples;
    int64_t maximum;

    if (!read_size_value(&scanner, &count) ||
        count == 0 ||
        count > SIZE_MAX / sizeof(*tuples)) {
        fputs("Invalid tuple count\n", stderr);
        return EXIT_FAILURE;
    }

    tuples = malloc(count * sizeof(*tuples));
    if (tuples == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_int32_value(&scanner, &tuples[i].first) ||
            !read_int32_value(&scanner, &tuples[i].second)) {
            fputs("Invalid tuple input\n", stderr);
            free(tuples);
            return EXIT_FAILURE;
        }
    }

    if (!find_maximum_product(tuples, count, &maximum)) {
        fputs("Unable to find maximum product\n", stderr);
        free(tuples);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", maximum) < 0) {
        free(tuples);
        return EXIT_FAILURE;
    }

    free(tuples);
    return EXIT_SUCCESS;
}