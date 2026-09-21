#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_of_squares(uint64_t n, uint64_t *result)
{
    __uint128_t value;

    if (result == NULL) {
        return -1;
    }

    value = (__uint128_t)n * ((__uint128_t)n + 1U) *
            (2U * (__uint128_t)n + 1U) / 6U;

    if (value > UINT64_MAX) {
        return -1;
    }

    *result = (uint64_t)value;
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
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(line, &end, 10);

    if (errno != 0 || end == line) {
        free(line);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || parsed > UINT64_MAX ||
        sum_of_squares((uint64_t)parsed, &result) != 0) {
        free(line);
        return EXIT_FAILURE;
    }

    free(line);

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}