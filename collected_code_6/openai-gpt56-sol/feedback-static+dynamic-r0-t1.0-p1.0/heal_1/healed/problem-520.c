#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t gcd_uint64(uint64_t a, uint64_t b)
{
    while (b != 0U) {
        uint64_t remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

static int lcm_array(const uint64_t values[], size_t count, uint64_t *result)
{
    uint64_t current = 1U;

    if (values == NULL || result == NULL || count == 0U) {
        return -1;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (values[i] == 0U) {
            *result = 0U;
            return 0;
        }

        uint64_t divisor = gcd_uint64(current, values[i]);
        uint64_t quotient = current / divisor;

        if (quotient > UINT64_MAX / values[i]) {
            return -1;
        }

        current = quotient * values[i];
    }

    *result = current;
    return 0;
}

static int read_line(char *buffer, size_t size)
{
    if (fgets(buffer, size, stdin) == NULL) {
        return -1;
    }

    for (size_t i = 0U; buffer[i] != '\0'; ++i) {
        if (buffer[i] == '\n') {
            buffer[i] = '\0';
            return 0;
        }
    }

    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }

    return -1;
}

static int read_size(size_t *value)
{
    char buffer[128];

    if (value == NULL || read_line(buffer, sizeof(buffer)) != 0) {
        return -1;
    }

    char *end = NULL;
    errno = 0;
    uintmax_t parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer) {
        return -1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0' || parsed == 0U || parsed > SIZE_MAX) {
        return -1;
    }

    *value = (size_t)parsed;
    return 0;
}

static int read_uint64(uint64_t *value)
{
    char buffer[128];

    if (value == NULL || read_line(buffer, sizeof(buffer)) != 0) {
        return -1;
    }

    char *start = buffer;
    while (*start == ' ' || *start == '\t' || *start == '\r' ||
           *start == '\v' || *start == '\f') {
        ++start;
    }

    if (*start == '-') {
        return -1;
    }

    char *end = NULL;
    errno = 0;
    uintmax_t parsed = strtoumax(start, &end, 10);

    if (errno == ERANGE || end == start || parsed > UINT64_MAX) {
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
    size_t count;

    if (read_size(&count) != 0 ||
        count > SIZE_MAX / sizeof(uint64_t)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    uint64_t *values = malloc(count * sizeof(*values));
    if (values == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (read_uint64(&values[i]) != 0) {
            fputs("Invalid input\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }
    }

    uint64_t result;
    if (lcm_array(values, count, &result) != 0) {
        fputs("LCM overflow\n", stderr);
        free(values);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    free(values);
    return EXIT_SUCCESS;
}