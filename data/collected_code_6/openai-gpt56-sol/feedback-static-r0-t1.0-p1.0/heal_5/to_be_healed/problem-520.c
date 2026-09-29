#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

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
        uint64_t value = values[i];

        if (value == 0) {
            *result = 0;
            return 0;
        }

        uint64_t quotient = current / gcd_uint64(current, value);

        if (quotient > UINT64_MAX / value) {
            return -1;
        }

        current = quotient * value;
    }

    *result = current;
    return 0;
}

static int read_line(FILE *stream, char **buffer, size_t *capacity)
{
    if (stream == NULL || buffer == NULL || capacity == NULL) {
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

        size_t available = *capacity - length;

        /* Possible weaknesses found:
         *  use of undeclared identifier 'INT_MAX'
         *  'INT_MAX' undeclared (first use in this function)
         *  each undeclared identifier is reported only once for each function it appears in
         */
        if (available > (size_t)INT_MAX) {
            /* Possible weaknesses found:
             *  use of undeclared identifier 'INT_MAX'
             */
            available = (size_t)INT_MAX;
        }

        if (fgets(*buffer + length, (int)available, stream) == NULL) {
            if (ferror(stream) || length == 0) {
                return -1;
            }

            (*buffer)[length] = '\0';
            return 0;
        }

        size_t added = 0;

        while (added < available && (*buffer)[length + added] != '\0') {
            ++added;
        }

        length += added;

        if (length > 0 && (*buffer)[length - 1] == '\n') {
            (*buffer)[--length] = '\0';

            if (length > 0 && (*buffer)[length - 1] == '\r') {
                (*buffer)[--length] = '\0';
            }

            return 0;
        }

        if (feof(stream)) {
            return 0;
        }
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
    size_t count = 0;
    uint64_t *values = NULL;
    int status = EXIT_FAILURE;

    if (read_line(stdin, &input, &input_capacity) != 0 ||
        parse_size(input, &count) != 0 ||
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
        if (read_line(stdin, &input, &input_capacity) != 0 ||
            parse_uint64(input, &values[i]) != 0) {
            fputs("Invalid input\n", stderr);
            goto cleanup;
        }
    }

    uint64_t result;

    if (lcm_array(values, count, &result) != 0) {
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
    free(input);
    return status;
}