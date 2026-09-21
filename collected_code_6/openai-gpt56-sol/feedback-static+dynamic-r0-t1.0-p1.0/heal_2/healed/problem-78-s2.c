#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int read_line(char **line)
{
    size_t length = 0;
    size_t capacity = 64;
    int ch;

    *line = malloc(capacity);
    if (*line == NULL) {
        return 0;
    }

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length + 1 >= capacity) {
            if (capacity > SIZE_MAX / 2) {
                free(*line);
                *line = NULL;
                return 0;
            }

            size_t new_capacity = capacity * 2;
            char *new_line = realloc(*line, new_capacity);

            if (new_line == NULL) {
                free(*line);
                *line = NULL;
                return 0;
            }

            *line = new_line;
            capacity = new_capacity;
        }

        (*line)[length++] = (char)ch;
    }

    if (ch == EOF && length == 0) {
        free(*line);
        *line = NULL;
        return 0;
    }

    (*line)[length] = '\0';
    return 1;
}

static int parse_uintmax(uintmax_t *value)
{
    char *line = NULL;

    if (!read_line(&line)) {
        return 0;
    }

    char *start = line;

    while (*start == ' ' || *start == '\t' ||
           *start == '\r' || *start == '\v' || *start == '\f') {
        ++start;
    }

    if (*start == '-' || *start == '\0') {
        free(line);
        return 0;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t parsed = strtoumax(start, &end, 10);

    if (errno == ERANGE || end == start) {
        free(line);
        return 0;
    }

    while (*end == ' ' || *end == '\t' ||
           *end == '\r' || *end == '\v' || *end == '\f') {
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

    if (!parse_uintmax(&parsed) || parsed > SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int read_uint64(uint64_t *value)
{
    uintmax_t parsed;

    if (!parse_uintmax(&parsed) || parsed > UINT64_MAX) {
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

    if (!read_size(&count)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    size_t odd_count = 0;

    for (size_t i = 0; i < count; ++i) {
        uint64_t value;

        if (!read_uint64(&value)) {
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }

        odd_count += has_odd_set_bits(value);
    }

    if (printf("%zu\n", odd_count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}