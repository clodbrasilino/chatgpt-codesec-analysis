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

    if (buffer == NULL || capacity == NULL) {
        return 0;
    }

    if (*buffer == NULL || *capacity == 0) {
        char *initial_buffer;
        size_t initial_capacity = 128;

        initial_buffer = malloc(initial_capacity);
        if (initial_buffer == NULL) {
            return 0;
        }

        *buffer = initial_buffer;
        *capacity = initial_capacity;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
                return 0;
            }
            break;
        }

        if (length == SIZE_MAX - 1) {
            return 0;
        }

        if (length + 1 >= *capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (*capacity > SIZE_MAX / 2) {
                return 0;
            }

            new_capacity = *capacity * 2;
            if (new_capacity <= length + 1) {
                return 0;
            }

            new_buffer = realloc(*buffer, new_capacity);
            if (new_buffer == NULL) {
                return 0;
            }

            *buffer = new_buffer;
            *capacity = new_capacity;
        }

        (*buffer)[length] = (char)ch;
        ++length;
    }

    if (length > 0 && (*buffer)[length - 1] == '\r') {
        --length;
    }

    (*buffer)[length] = '\0';
    return 1;
}

static int parse_uintmax_value(const char *text, uintmax_t maximum,
                               uintmax_t *value)
{
    char *end;
    uintmax_t parsed;

    if (text == NULL || value == NULL || *text == '\0' ||
        *text == '-' || *text == '+') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || parsed > maximum) {
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *value = parsed;
    return 1;
}

static int parse_size(const char *text, size_t *value)
{
    uintmax_t parsed;

    if (value == NULL ||
        !parse_uintmax_value(text, (uintmax_t)SIZE_MAX, &parsed)) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int parse_uint64(const char *text, uint64_t *value)
{
    uintmax_t parsed;

    if (value == NULL ||
        !parse_uintmax_value(text, (uintmax_t)UINT64_MAX, &parsed)) {
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
    uint64_t *values = NULL;
    uint64_t result;
    int status = EXIT_FAILURE;

    if (!read_line(&line, &line_capacity) ||
        !parse_size(line, &count) ||
        count == 0 ||
        count > SIZE_MAX / sizeof(*values)) {
        fputs("Invalid input\n", stderr);
        goto cleanup;
    }

    values = malloc(count * sizeof(*values));
    if (values == NULL) {
        fputs("Memory allocation failed\n", stderr);
        goto cleanup;
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_line(&line, &line_capacity) ||
            !parse_uint64(line, &values[i])) {
            fputs("Invalid input\n", stderr);
            goto cleanup;
        }
    }

    if (!lcm_array(values, count, &result)) {
        fputs("LCM overflow\n", stderr);
        goto cleanup;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        fputs("Output error\n", stderr);
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(values);
    free(line);
    return status;
}