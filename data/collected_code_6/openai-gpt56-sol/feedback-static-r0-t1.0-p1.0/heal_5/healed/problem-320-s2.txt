#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_difference(uint64_t n, uint64_t *result)
{
    __uint128_t value;
    __uint128_t sum;
    __uint128_t sum_of_squares;
    __uint128_t difference;

    if (result == NULL) {
        return 0;
    }

    value = (__uint128_t)n;
    sum = value * (value + 1) / 2;
    sum_of_squares = value * (value + 1) * (2 * value + 1) / 6;
    difference = sum * sum - sum_of_squares;

    if (difference > UINT64_MAX) {
        return 0;
    }

    *result = (uint64_t)difference;
    return 1;
}

static int read_uint64(uint64_t *value)
{
    char buffer[256];
    char *end;
    uintmax_t parsed;
    int ch;

    if (value == NULL) {
        return 0;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    end = buffer;
    while (*end != '\0' && *end != '\n') {
        ++end;
    }

    if (*end != '\n') {
        if (!feof(stdin)) {
            while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
            }
        }
        return 0;
    }

    *end = '\0';

    ch = fgetc(stdin);
    if (ch != EOF) {
        return 0;
    }
    if (ferror(stdin)) {
        return 0;
    }

    end = buffer;
    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end == '-') {
        return 0;
    }

    if (*end == '+') {
        ++end;
    }

    if (!isdigit((unsigned char)*end)) {
        return 0;
    }

    parsed = 0;
    do {
        unsigned int digit = (unsigned int)(*end - '0');

        if (parsed > (UINT64_MAX - digit) / 10) {
            return 0;
        }

        parsed = parsed * 10 + digit;
        ++end;
    } while (isdigit((unsigned char)*end));

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *value = (uint64_t)parsed;
    return 1;
}

int main(void)
{
    uint64_t input;
    uint64_t difference;

    if (!read_uint64(&input)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!calculate_difference(input, &difference)) {
        fputs("Result exceeds the supported range\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", difference) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}