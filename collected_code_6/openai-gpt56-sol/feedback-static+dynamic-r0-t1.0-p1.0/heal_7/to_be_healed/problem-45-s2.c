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

static int read_line(char **buffer, size_t *capacity)
{
    size_t length = 0;

    if (buffer == NULL || capacity == NULL) {
        return 0;
    }

    if (*buffer == NULL || *capacity < 2) {
        char *new_buffer = realloc(*buffer, 128);

        if (new_buffer == NULL) {
            return 0;
        }

        *buffer = new_buffer;
        *capacity = 128;
    }

    for (;;) {
        int ch;

        if (length + 1 >= *capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (*capacity > SIZE_MAX / 2) {
                if (*capacity == SIZE_MAX) {
                    return 0;
                }
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = *capacity * 2;
            }

            if (new_capacity <= *capacity) {
                return 0;
            }

            new_buffer = realloc(*buffer, new_capacity);
            if (new_buffer == NULL) {
                return 0;
            }

            *buffer = new_buffer;
            *capacity = new_capacity;
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);

        if (ch == '\n' || ch == EOF) {
            if (ch == EOF && ferror(stdin)) {
                return 0;
            }

            if (ch == EOF && length == 0) {
                return 0;
            }

            break;
        }

        (*buffer)[length++] = (char)(unsigned char)ch;
    }

    if (length > 0 && (*buffer)[length - 1] == '\r') {
        --length;
    }

    (*buffer)[length] = '\0';
    return 1;
}

static int parse_size(const char *text, size_t *value)
{
    char *end = NULL;
    uintmax_t parsed;

    if (text == NULL || value == NULL || *text == '\0' ||
        *text == '-' || *text == '+') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed == 0 || parsed > SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int parse_int64(const char *text, int64_t *value)
{
    char *end = NULL;
    intmax_t parsed;

    if (text == NULL || value == NULL || *text == '\0') {
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
    char *buffer = NULL;
    size_t capacity = 0;
    size_t count;
    uint64_t result = 0;

    if (!read_line(&buffer, &capacity) ||
        !parse_size(buffer, &count)) {
        fputs("Invalid input\n", stderr);
        free(buffer);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        int64_t value;

        if (!read_line(&buffer, &capacity) ||
            !parse_int64(buffer, &value)) {
            fputs("Invalid input\n", stderr);
            free(buffer);
            return EXIT_FAILURE;
        }

        result = gcd_pair(result, magnitude(value));
    }

    free(buffer);

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}