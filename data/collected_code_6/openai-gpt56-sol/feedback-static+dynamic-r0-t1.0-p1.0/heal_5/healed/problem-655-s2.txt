#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_of_fifth_powers(uint64_t n, uint64_t *result)
{
    const uint64_t maximum_n = 1388;
    __uint128_t sum = 0;

    if (result == NULL || n > maximum_n) {
        return -1;
    }

    for (uint64_t i = 1; i <= n; ++i) {
        const __uint128_t value = i;
        sum += value * value * value * value * value;
    }

    *result = (uint64_t)sum;
    return 0;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end;
    uintmax_t parsed;
    uint64_t result;

    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = line;
    parsed = strtoumax(line, &end, 10);

    if (end == line || errno == ERANGE || parsed > UINT64_MAX ||
        line[0] == '-') {
        free(line);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\n' || *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    free(line);

    if (sum_of_fifth_powers((uint64_t)parsed, &result) != 0) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}