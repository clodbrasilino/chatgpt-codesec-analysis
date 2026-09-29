#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

static int cube_sum(uint64_t n, uint64_t *result)
{
    uint64_t a;
    uint64_t b;

    if (result == NULL || n == UINT64_MAX) {
        return 0;
    }

    a = n;
    b = n + UINT64_C(1);

    if ((a & UINT64_C(1)) == 0) {
        a /= UINT64_C(2);
    } else {
        b /= UINT64_C(2);
    }

    if (a != 0 && b > UINT64_MAX / a) {
        return 0;
    }

    a *= b;

    if (a != 0 && a > UINT64_MAX / a) {
        return 0;
    }

    *result = a * a;
    return 1;
}

static int read_line(char **line)
{
    char *buffer;
    size_t length = 0;
    size_t capacity = 64;

    if (line == NULL) {
        return 0;
    }

    *line = NULL;
    buffer = malloc(capacity);

    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        size_t available;
        size_t chunk_length;

        if (length > SIZE_MAX - 2) {
            free(buffer);
            return 0;
        }

        if (capacity - length < 2) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return 0;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        available = capacity - length;

        if (available > (size_t)INT_MAX) {
            available = (size_t)INT_MAX;
        }

        if (fgets(buffer + length, (int)available, stdin) == NULL) {
            if (ferror(stdin) || length == 0) {
                free(buffer);
                return 0;
            }

            buffer[length] = '\0';
            break;
        }

        chunk_length = strlen(buffer + length);
        length += chunk_length;

        if (length != 0 && buffer[length - 1] == '\n') {
            buffer[--length] = '\0';

            if (length != 0 && buffer[length - 1] == '\r') {
                buffer[--length] = '\0';
            }

            break;
        }

        if (feof(stdin)) {
            break;
        }
    }

    *line = buffer;
    return 1;
}

int main(void)
{
    char *input;
    char *start;
    char *end;
    uintmax_t value;
    uint64_t result;

    if (!read_line(&input)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    start = input;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-' || *start == '\0') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(start, &end, 10);

    if (end == start) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (errno == ERANGE || value > UINT64_MAX) {
        free(input);
        fputs("Input exceeds the uint64_t range\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (!cube_sum((uint64_t)value, &result)) {
        fputs("Result exceeds the uint64_t range\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}