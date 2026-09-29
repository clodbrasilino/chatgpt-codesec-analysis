#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t magnitude(int64_t value)
{
    return value >= 0
        ? (uint64_t)value
        : (uint64_t)(-(value + INT64_C(1))) + UINT64_C(1);
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

static uint64_t gcd_array(const int64_t values[], size_t count)
{
    uint64_t result = 0;

    for (size_t i = 0; i < count; ++i) {
        result = gcd_pair(result, magnitude(values[i]));
    }

    return result;
}

static int read_line(char *buffer, size_t size)
{
    if (fgets(buffer, (int)size, stdin) == NULL) {
        return 0;
    }

    size_t i = 0;
    while (buffer[i] != '\0' && buffer[i] != '\n') {
        ++i;
    }

    if (buffer[i] == '\n') {
        buffer[i] = '\0';
        return 1;
    }

    if (buffer[i] == '\0' && feof(stdin)) {
        return 1;
    }

    int ch;
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }

    return 0;
}

static int parse_size(const char *text, size_t *value)
{
    char *end;
    uintmax_t parsed;

    if (*text == '\0' || *text == '-') {
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
    char *end;
    intmax_t parsed;

    if (*text == '\0') {
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    size_t count;

    if (!read_line(buffer, sizeof(buffer)) ||
        !parse_size(buffer, &count) ||
        count > SIZE_MAX / sizeof(int64_t)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    int64_t *values = malloc(count * sizeof(*values));
    if (values == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_line(buffer, sizeof(buffer)) ||
            !parse_int64(buffer, &values[i])) {
            fputs("Invalid input\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }
    }

    uint64_t result = gcd_array(values, count);
    free(values);

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}