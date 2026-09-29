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

    return (uint64_t)(-(value + 1)) + UINT64_C(1);
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

static int parse_count(const char *text, size_t *count)
{
    char *end;
    uintmax_t value;

    if (text[0] == '-') {
        return 0;
    }

    errno = 0;
    value = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        value == 0 || value > SIZE_MAX / sizeof(int64_t)) {
        return 0;
    }

    *count = (size_t)value;
    return 1;
}

static int parse_int64(const char *text, int64_t *value)
{
    char *end;
    intmax_t parsed;

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
    char buffer[256];
    size_t count;
    uint64_t result = 0;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    char *newline = buffer;
    while (*newline != '\0' && *newline != '\n') {
        ++newline;
    }

    if (*newline != '\n' && !feof(stdin)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    *newline = '\0';

    if (!parse_count(buffer, &count)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    int64_t *values = malloc(count * sizeof(*values));
    if (values == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            fputs("Invalid input\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }

        newline = buffer;
        while (*newline != '\0' && *newline != '\n') {
            ++newline;
        }

        if (*newline != '\n' && !feof(stdin)) {
            fputs("Invalid input\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }

        *newline = '\0';

        if (!parse_int64(buffer, &values[i])) {
            fputs("Invalid input\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }

        result = gcd_pair(result, magnitude(values[i]));
    }

    free(values);

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}