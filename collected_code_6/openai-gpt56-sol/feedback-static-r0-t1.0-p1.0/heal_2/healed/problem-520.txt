#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t gcd_uint64(uint64_t a, uint64_t b)
{
    while (b != 0) {
        uint64_t remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

static int lcm_array(const uint64_t values[], size_t count, uint64_t *result)
{
    if (values == NULL || result == NULL || count == 0) {
        return -1;
    }

    uint64_t current = 1;

    for (size_t i = 0; i < count; ++i) {
        if (values[i] == 0) {
            *result = 0;
            return 0;
        }

        uint64_t quotient = current / gcd_uint64(current, values[i]);

        if (quotient > UINT64_MAX / values[i]) {
            return -1;
        }

        current = quotient * values[i];
    }

    *result = current;
    return 0;
}

static int read_line(char **buffer, size_t *capacity)
{
    if (buffer == NULL || capacity == NULL) {
        return -1;
    }

    if (*buffer == NULL || *capacity < 2) {
        size_t initial_capacity = 128;
        char *new_buffer = malloc(initial_capacity);

        if (new_buffer == NULL) {
            return -1;
        }

        free(*buffer);
        *buffer = new_buffer;
        *capacity = initial_capacity;
    }

    size_t length = 0;

    for (;;) {
        int ch = fgetc(stdin);

        if (ch == '\n') {
            (*buffer)[length] = '\0';
            return 0;
        }

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
                return -1;
            }

            (*buffer)[length] = '\0';
            return 0;
        }

        if (length + 1 >= *capacity) {
            if (*capacity > SIZE_MAX / 2) {
                return -1;
            }

            size_t new_capacity = *capacity * 2;
            char *new_buffer = realloc(*buffer, new_capacity);

            if (new_buffer == NULL) {
                return -1;
            }

            *buffer = new_buffer;
            *capacity = new_capacity;
        }

        (*buffer)[length++] = (char)ch;
    }
}

static int parse_size(const char *text, size_t *value)
{
    if (text == NULL || value == NULL || *text == '\0' || *text == '-') {
        return -1;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text) {
        return -1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0' || parsed == 0 || parsed > SIZE_MAX) {
        return -1;
    }

    *value = (size_t)parsed;
    return 0;
}

static int parse_uint64(const char *text, uint64_t *value)
{
    if (text == NULL || value == NULL || *text == '\0' || *text == '-') {
        return -1;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || parsed > UINT64_MAX) {
        return -1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *value = (uint64_t)parsed;
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t input_capacity = 0;
    size_t count;

    if (read_line(&input, &input_capacity) != 0 ||
        parse_size(input, &count) != 0 ||
        count > SIZE_MAX / sizeof(uint64_t)) {
        fputs("Invalid input\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    uint64_t *values = malloc(count * sizeof(*values));

    if (values == NULL) {
        fputs("Memory allocation failed\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (read_line(&input, &input_capacity) != 0 ||
            parse_uint64(input, &values[i]) != 0) {
            fputs("Invalid input\n", stderr);
            free(values);
            free(input);
            return EXIT_FAILURE;
        }
    }

    uint64_t result;

    if (lcm_array(values, count, &result) != 0) {
        fputs("LCM overflow\n", stderr);
        free(values);
        free(input);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);

    free(values);
    free(input);
    return EXIT_SUCCESS;
}