#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_difference(uint64_t n, uint64_t *result)
{
    __uint128_t sum;
    __uint128_t difference;

    if (result == NULL) {
        return 0;
    }

    sum = (__uint128_t)n * ((__uint128_t)n + 1U) / 2U;
    difference = sum * sum - sum;

    if (difference > UINT64_MAX) {
        return 0;
    }

    *result = (uint64_t)difference;
    return 1;
}

static int read_value(uint64_t *result)
{
    char buffer[128];
    char *start;
    char *end;
    uintmax_t value;

    if (result == NULL || fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    if (buffer[0] != '\0' && buffer[strlen(buffer) - 1U] != '\n') {
        int ch;

        ch = getchar();
        if (ch != EOF) {
            while (ch != '\n' && ch != EOF) {
                ch = getchar();
            }
            return 0;
        }
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-') {
        return 0;
    }

    errno = 0;
    value = strtoumax(start, &end, 10);

    if (start == end || errno == ERANGE || value > UINT64_MAX) {
        return 0;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *result = (uint64_t)value;
    return 1;
}

int main(void)
{
    uint64_t value;
    uint64_t difference;

    if (!read_value(&value)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!calculate_difference(value, &difference)) {
        fputs("Result is out of range\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", difference);
    return EXIT_SUCCESS;
}