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

static int read_line(char *buffer, size_t size)
{
    int ch;

    if (buffer == NULL || size < 2 || fgets(buffer, (int)size, stdin) == NULL) {
        return -1;
    }

    for (size_t i = 0; buffer[i] != '\0'; ++i) {
        if (buffer[i] == '\n') {
            return 0;
        }
    }

    if (feof(stdin)) {
        return 0;
    }

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
    }

    return -1;
}

static int read_size(size_t *value)
{
    char buffer[256];
    char *end;
    uintmax_t parsed;

    if (value == NULL || read_line(buffer, sizeof buffer) != 0) {
        return -1;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    if (end == buffer || errno == ERANGE || parsed == 0 ||
        parsed > (uintmax_t)SIZE_MAX) {
        return -1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\n' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *value = (size_t)parsed;
    return 0;
}

static int read_int64(int64_t *value)
{
    char buffer[256];
    char *end;
    intmax_t parsed;

    if (value == NULL || read_line(buffer, sizeof buffer) != 0) {
        return -1;
    }

    errno = 0;
    parsed = strtoimax(buffer, &end, 10);

    if (end == buffer || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return -1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\n' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *value = (int64_t)parsed;
    return 0;
}

int main(void)
{
    size_t count;
    uint64_t result = 0;

    if (read_size(&count) != 0) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        int64_t value;

        if (read_int64(&value) != 0) {
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }

        result = gcd_pair(result, magnitude(value));
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}