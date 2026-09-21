#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t magnitude(int64_t value)
{
    if (value >= 0) {
        return (uint64_t)value;
    }

    return (uint64_t)(-(value + INT64_C(1))) + UINT64_C(1);
}

static uint64_t gcd_pair(uint64_t a, uint64_t b)
{
    while (b != 0) {
        uint64_t remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

static int read_line(char **line, size_t *capacity)
{
    size_t length = 0;
    int character = EOF;

    if (line == NULL || capacity == NULL) {
        return -1;
    }

    if (*line == NULL || *capacity < 2) {
        char *buffer;
        size_t initial_capacity = 128;

        buffer = realloc(*line, initial_capacity);
        if (buffer == NULL) {
            return -1;
        }

        *line = buffer;
        *capacity = initial_capacity;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);

        if (character == EOF || character == '\n') {
            break;
        }

        if (length + 1 >= *capacity) {
            size_t new_capacity;
            char *resized;

            if (*capacity > SIZE_MAX / 2) {
                return -1;
            }

            new_capacity = *capacity * 2;
            resized = realloc(*line, new_capacity);
            if (resized == NULL) {
                return -1;
            }

            *line = resized;
            *capacity = new_capacity;
        }

        (*line)[length++] = (char)(unsigned char)character;
    }

    if (character == EOF) {
        if (ferror(stdin)) {
            return -1;
        }

        if (length == 0) {
            return 0;
        }
    }

    if (length > 0 && (*line)[length - 1] == '\r') {
        --length;
    }

    (*line)[length] = '\0';
    return 1;
}

static int parse_count(const char *text, size_t *count)
{
    char *end = NULL;
    uintmax_t value;

    if (text == NULL || count == NULL || text[0] == '\0' ||
        text[0] == '-' || text[0] == '+') {
        return 0;
    }

    errno = 0;
    value = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        value == 0 || value > SIZE_MAX) {
        return 0;
    }

    *count = (size_t)value;
    return 1;
}

static int parse_int64(const char *text, int64_t *value)
{
    char *end = NULL;
    intmax_t parsed;

    if (text == NULL || value == NULL || text[0] == '\0') {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    size_t count;
    uint64_t result = 0;
    int status;

    status = read_line(&line, &capacity);
    if (status != 1 || !parse_count(line, &count)) {
        fputs("Invalid input\n", stderr);
        free(line);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        int64_t value;

        status = read_line(&line, &capacity);
        if (status != 1 || !parse_int64(line, &value)) {
            fputs("Invalid input\n", stderr);
            free(line);
            return EXIT_FAILURE;
        }

        result = gcd_pair(result, magnitude(value));
    }

    free(line);

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}