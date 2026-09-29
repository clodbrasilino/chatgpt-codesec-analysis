#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uintmax_t magnitude(intmax_t value)
{
    return value < 0
        ? (uintmax_t)(-(value + 1)) + UINTMAX_C(1)
        : (uintmax_t)value;
}

static uintmax_t gcd_pair(uintmax_t a, uintmax_t b)
{
    while (b != 0) {
        uintmax_t remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

static uintmax_t gcd_array(const intmax_t values[], size_t count)
{
    uintmax_t result = 0;

    for (size_t i = 0; i < count; ++i) {
        result = gcd_pair(result, magnitude(values[i]));
    }

    return result;
}

static int read_intmax(intmax_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    char *end;
    errno = 0;
    intmax_t parsed = strtoimax(buffer, &end, 10);

    if (end == buffer || errno == ERANGE) {
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *value = parsed;
    return 1;
}

static int read_size(size_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    char *start = buffer;
    while (*start == ' ' || *start == '\t' || *start == '\r' ||
           *start == '\n' || *start == '\f' || *start == '\v') {
        ++start;
    }

    if (*start == '-') {
        return 0;
    }

    char *end;
    errno = 0;
    uintmax_t parsed = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE || parsed == 0 ||
        parsed > SIZE_MAX / sizeof(intmax_t)) {
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

int main(void)
{
    size_t count;

    if (!read_size(&count)) {
        fputs("Invalid array size\n", stderr);
        return EXIT_FAILURE;
    }

    intmax_t *values = malloc(count * sizeof *values);
    if (values == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_intmax(&values[i])) {
            fputs("Invalid array element\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }
    }

    uintmax_t result = gcd_array(values, count);
    free(values);

    if (printf("%" PRIuMAX "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}