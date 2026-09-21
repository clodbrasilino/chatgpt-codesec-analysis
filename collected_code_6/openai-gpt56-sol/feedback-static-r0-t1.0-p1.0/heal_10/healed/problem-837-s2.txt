#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int cube_sum_first_n_odds(uint64_t n, uint64_t *result)
{
    uint64_t square;

    if (result == NULL || n > UINT64_C(55108)) {
        return 0;
    }

    square = n * n;
    *result = square * (UINT64_C(2) * square - UINT64_C(1));
    return 1;
}

static int read_uint64(uint64_t *value)
{
    char buffer[128];
    char *end;
    uintmax_t parsed;
    int ch;

    if (value == NULL || fgets(buffer, sizeof buffer, stdin) == NULL) {
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
    end = buffer;

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end == '\0' || *end == '-') {
        return 0;
    }

    if (*end == '+') {
        ++end;
    }

    if (!isdigit((unsigned char)*end)) {
        return 0;
    }

    parsed = 0;
    while (isdigit((unsigned char)*end)) {
        unsigned int digit = (unsigned int)(*end - '0');

        if (parsed > (UINT64_MAX - digit) / UINT64_C(10)) {
            return 0;
        }

        parsed = parsed * UINT64_C(10) + digit;
        ++end;
    }

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
    uint64_t value;
    uint64_t result;

    if (!read_uint64(&value)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!cube_sum_first_n_odds(value, &result)) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}