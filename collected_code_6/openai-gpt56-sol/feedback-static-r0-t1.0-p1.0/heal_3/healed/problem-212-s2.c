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

    if (result == NULL || n == 0 || n > UINT64_C(92681)) {
        return 0;
    }

    factors[0] = n;
    factors[1] = n + UINT64_C(1);
    factors[2] = UINT64_C(2) * n + UINT64_C(1);
    factors[3] = UINT64_C(3) * n * n + UINT64_C(3) * n - UINT64_C(1);

    for (i = 0; i < sizeof factors / sizeof factors[0]; ++i) {
        uint64_t factor = factors[i];
        uint64_t candidate;

        for (candidate = UINT64_C(2);
             candidate <= divisor / candidate;
             ++candidate) {
            while (divisor % candidate == 0 &&
                   factor % candidate == 0) {
                divisor /= candidate;
                factor /= candidate;
            }
        }

        if (divisor > 1 && factor % divisor == 0) {
            factor /= divisor;
            divisor = 1;
        }

        factors[i] = factor;
    }

    if (divisor != 1) {
        return 0;
    }

    for (i = 0; i < sizeof factors / sizeof factors[0]; ++i) {
        if (value > UINT64_MAX / factors[i]) {
            return 0;
        }
        value *= factors[i];
    }

    *result = value;
    return 1;
}

static int read_line(char *buffer, size_t capacity)
{
    size_t length;

    if (buffer == NULL || capacity < 2) {
        return 0;
    }

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        return 0;
    }

    for (length = 0; length < capacity; ++length) {
        if (buffer[length] == '\0') {
            break;
        }
    }

    if (length == capacity) {
        return 0;
    }

    if (length > 0 && buffer[length - 1] == '\n') {
        return 1;
    }

    if (feof(stdin)) {
        return 1;
    }

    {
        char discard[128];

        do {
            if (fgets(discard, sizeof discard, stdin) == NULL) {
                break;
            }

            for (length = 0; length < sizeof discard; ++length) {
                if (discard[length] == '\0' || discard[length] == '\n') {
                    break;
                }
            }
        } while (length == sizeof discard ||
                 (length > 0 && discard[length] != '\n'));
    }

    return 0;
}

int main(void)
{
    char input[128];
    char *end;
    uintmax_t parsed;
    uint64_t result;

    if (!read_line(input, sizeof input)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(input, &end, 10);

    if (end == input || errno == ERANGE || parsed > UINT64_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

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