#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int read_line(char **line)
{
    char *buffer = NULL;
    size_t length = 0;
    size_t capacity = 64;
    int ch;

    if (line == NULL) {
        return 0;
    }

    *line = NULL;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);

        if (ch == EOF || ch == '\n') {
            break;
        }

        if (length >= SIZE_MAX - 1) {
            free(buffer);
            return 0;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity <= length + 1) {
                free(buffer);
                return 0;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return 0;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ferror(stdin) || (ch == EOF && length == 0)) {
        free(buffer);
        return 0;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

static int parse_uintmax(uintmax_t *value)
{
    char *line;
    char *start;
    char *end;
    uintmax_t parsed;

    if (value == NULL || !read_line(&line)) {
        return 0;
    }

    start = line;
    while (*start == ' ' || *start == '\t' || *start == '\r' ||
           *start == '\v' || *start == '\f') {
        ++start;
    }

    if (*start == '\0' || *start == '+' || *start == '-') {
        free(line);
        return 0;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (errno == ERANGE || end == start) {
        free(line);
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return 0;
    }

    *value = parsed;
    free(line);
    return 1;
}

static int read_size(size_t *value)
{
    uintmax_t parsed;

    if (value == NULL || !parse_uintmax(&parsed) ||
        parsed > (uintmax_t)SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int read_uint64(uint64_t *value)
{
    uintmax_t parsed;

    if (value == NULL || !parse_uintmax(&parsed) ||
        parsed > (uintmax_t)UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)parsed;
    return 1;
}

static unsigned int has_odd_set_bits(uint64_t value)
{
    unsigned int parity = 0;

    while (value != UINT64_C(0)) {
        parity ^= 1U;
        value &= value - UINT64_C(1);
    }

    return parity;
}

int main(void)
{
    size_t count;
    size_t odd_count = 0;

    if (!read_size(&count)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        uint64_t value;

        if (!read_uint64(&value)) {
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }

        odd_count += (size_t)has_odd_set_bits(value);
    }

    if (printf("%zu\n", odd_count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}