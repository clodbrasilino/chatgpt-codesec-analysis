#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

enum { INITIAL_LINE_CAPACITY = 128 };

static int read_line(char **buffer, size_t *capacity)
{
    if (buffer == NULL || capacity == NULL) {
        return -1;
    }

    size_t length = 0;

    for (;;) {
        int ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
                return -1;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length > SIZE_MAX - 2) {
            return -1;
        }

        size_t required = length + 2;

        if (required > *capacity) {
            size_t new_capacity = *capacity;

            if (new_capacity == 0) {
                new_capacity = INITIAL_LINE_CAPACITY;
            }

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2;
            }

            char *new_buffer = realloc(*buffer, new_capacity);

            if (new_buffer == NULL) {
                return -1;
            }

            *buffer = new_buffer;
            *capacity = new_capacity;
        }

        (*buffer)[length++] = (char)(unsigned char)ch;
    }

    if (length > 0 && (*buffer)[length - 1] == '\r') {
        --length;
    }

    if (length == SIZE_MAX) {
        return -1;
    }

    size_t required = length + 1;

    if (required > *capacity) {
        char *new_buffer = realloc(*buffer, required);

        if (new_buffer == NULL) {
            return -1;
        }

        *buffer = new_buffer;
        *capacity = required;
    }

    (*buffer)[length] = '\0';
    return 0;
}

static int parse_uintmax(const char *text, uintmax_t *value)
{
    if (text == NULL || value == NULL) {
        return -1;
    }

    while (isspace((unsigned char)*text)) {
        ++text;
    }

    if (*text == '\0' || *text == '+' || *text == '-') {
        return -1;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text) {
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *value = parsed;
    return 0;
}

static int parse_intmax(const char *text, intmax_t *value)
{
    if (text == NULL || value == NULL) {
        return -1;
    }

    while (isspace((unsigned char)*text)) {
        ++text;
    }

    if (*text == '\0') {
        return -1;
    }

    errno = 0;
    char *end = NULL;
    intmax_t parsed = strtoimax(text, &end, 10);

    if (errno == ERANGE || end == text) {
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *value = parsed;
    return 0;
}

static int largest_adjacent_product(const int32_t *values,
                                    size_t count,
                                    int64_t *result)
{
    if (values == NULL || result == NULL || count < 2) {
        return -1;
    }

    int64_t largest = (int64_t)values[0] * (int64_t)values[1];

    for (size_t i = 1; i < count - 1; ++i) {
        int64_t product = (int64_t)values[i] * (int64_t)values[i + 1];

        if (product > largest) {
            largest = product;
        }
    }

    *result = largest;
    return 0;
}

int main(void)
{
    char *line = NULL;
    size_t line_capacity = 0;
    uintmax_t input_count = 0;
    int32_t *values = NULL;
    int status = EXIT_FAILURE;

    if (read_line(&line, &line_capacity) != 0 ||
        parse_uintmax(line, &input_count) != 0 ||
        input_count < 2 ||
        input_count > SIZE_MAX ||
        input_count > SIZE_MAX / sizeof(*values)) {
        fputs("Invalid input\n", stderr);
        goto cleanup;
    }

    size_t count = (size_t)input_count;
    values = malloc(count * sizeof(*values));

    if (values == NULL) {
        perror("malloc");
        goto cleanup;
    }

    for (size_t i = 0; i < count; ++i) {
        intmax_t input = 0;

        if (read_line(&line, &line_capacity) != 0 ||
            parse_intmax(line, &input) != 0 ||
            input < INT32_MIN ||
            input > INT32_MAX) {
            fputs("Invalid input\n", stderr);
            goto cleanup;
        }

        values[i] = (int32_t)input;
    }

    int64_t result = 0;

    if (largest_adjacent_product(values, count, &result) != 0) {
        fputs("Unable to calculate product\n", stderr);
        goto cleanup;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        fputs("Output error\n", stderr);
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(values);
    free(line);
    return status;
}