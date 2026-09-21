#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_fourth_powers(uint64_t n, uint64_t *result)
{
    uint64_t factors[4];
    uint64_t divisor = UINT64_C(30);
    uint64_t value = UINT64_C(1);
    size_t i;

    if (result == NULL) {
        return 0;
    }

    if (n > UINT64_C(92681)) {
        return 0;
    }

    factors[0] = n;
    factors[1] = n + UINT64_C(1);
    factors[2] = UINT64_C(2) * n + UINT64_C(1);
    factors[3] = UINT64_C(3) * n * n + UINT64_C(3) * n - UINT64_C(1);

    for (i = 0; i < 4 && divisor > UINT64_C(1); ++i) {
        uint64_t candidate;

        for (candidate = UINT64_C(2); candidate <= divisor; ++candidate) {
            while (divisor % candidate == 0 &&
                   factors[i] % candidate == 0) {
                divisor /= candidate;
                factors[i] /= candidate;
            }
        }
    }

    if (divisor != UINT64_C(1)) {
        return 0;
    }

    for (i = 0; i < 4; ++i) {
        if (factors[i] != 0 && value > UINT64_MAX / factors[i]) {
            return 0;
        }
        value *= factors[i];
    }

    *result = value;
    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end;
    uintmax_t parsed;
    uint64_t result;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = input;
    parsed = strtoumax(input, &end, 10);

    if (end == input || errno == ERANGE || parsed > UINT64_MAX) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (parsed == 0 || parsed > UINT64_C(92681) ||
        !sum_fourth_powers((uint64_t)parsed, &result)) {
        fputs("Input is out of range\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}