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
    uint64_t current;

    if (values == NULL || result == NULL || count == 0) {
        return 0;
    }

    current = values[0];

    for (size_t i = 1; i < count; ++i) {
        uint64_t divisor;
        uint64_t factor;

        if (current == 0 || values[i] == 0) {
            current = 0;
            continue;
        }

        divisor = gcd_uint64(current, values[i]);
        factor = current / divisor;

        if (factor > UINT64_MAX / values[i]) {
            return 0;
        }

        current = factor * values[i];
    }

    *result = current;
    return 1;
}

static int read_line(char **buffer, size_t *capacity)
{
    size_t length = 0;
    int ch;

    if (buffer == NULL || capacity == NULL) {
        return 0;
    }

    if (*buffer == NULL || *capacity == 0) {
        *capacity = 128;
        *buffer = malloc(*capacity);
        if (*buffer == NULL) {
            return 0;
        }
    }

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length + 1 >= *capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (*capacity > SIZE_MAX / 2) {
                return 0;
            }

            new_capacity = *capacity * 2;
            new_buffer = realloc(*buffer, new_capacity);
            if (new_buffer == NULL) {
                return 0;
            }

            *buffer = new_buffer;
            *capacity = new_capacity;
        }

        (*buffer)[length++] = (char)ch;
    }

    if (ch == EOF && length == 0) {
        return 0;
    }

    (*buffer)[length] = '\0';
    return 1;
}

static int parse_size(const char *text, size_t *value)
{
    char *end;
    uintmax_t parsed;

    if (text == NULL || value == NULL || *text == '\0' || *text == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || parsed > SIZE_MAX) {
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int parse_uint64(const char *text, uint64_t *value)
{
    char *end;
    uintmax_t parsed;

    if (text == NULL || value == NULL || *text == '\0' || *text == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || parsed > UINT64_MAX) {
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *value = (uint64_t)parsed;
    return 1;
}

int main(void)
{
    char *line = NULL;
    size_t line_capacity = 0;
    size_t count;
    uint64_t *values;
    uint64_t result;

    if (!read_line(&line, &line_capacity) ||
        !parse_size(line, &count) ||
        count == 0 ||
        count > SIZE_MAX / sizeof(*values)) {
        fputs("Invalid input\n", stderr);
        free(line);
        return EXIT_FAILURE;
    }

    values = malloc(count * sizeof(*values));
    if (values == NULL) {
        fputs("Memory allocation failed\n", stderr);
        free(line);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_line(&line, &line_capacity) ||
            !parse_uint64(line, &values[i])) {
            fputs("Invalid input\n", stderr);
            free(values);
            free(line);
            return EXIT_FAILURE;
        }
    }

    free(line);

    if (!lcm_array(values, count, &result)) {
        fputs("LCM overflow\n", stderr);
        free(values);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    free(values);
    return EXIT_SUCCESS;
}