#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_difference(uint64_t n, uint64_t *result)
{
    const __uint128_t value = n;
    const __uint128_t sum = value * (value + 1) / 2;
    const __uint128_t sum_of_squares =
        value * (value + 1) * (2 * value + 1) / 6;
    const __uint128_t difference = sum * sum - sum_of_squares;

    if (difference > UINT64_MAX) {
        return 0;
    }

    *result = (uint64_t)difference;
    return 1;
}

static int read_uint64(uint64_t *value)
{
    char input[128];
    char *end;
    uintmax_t parsed;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return 0;
    }

    for (size_t i = 0; input[i] != '\0'; ++i) {
        if (input[i] == '\n') {
            input[i] = '\0';
            break;
        }

        if (i == sizeof input - 2) {
            int ch = fgetc(stdin);

            if (ch != '\n' && ch != EOF) {
                do {
                    ch = fgetc(stdin);
                } while (ch != '\n' && ch != EOF);

                return 0;
            }
        }
    }

    errno = 0;
    parsed = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input || parsed > UINT64_MAX) {
        return 0;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
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