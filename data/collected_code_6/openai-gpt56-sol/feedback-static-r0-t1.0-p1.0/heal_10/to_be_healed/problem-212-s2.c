#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
    MAX_INPUT_LENGTH = 1024
};

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
            while (divisor % candidate == 0 && factor % candidate == 0) {
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
        if (factors[i] != 0 && value > UINT64_MAX / factors[i]) {
            return 0;
        }
        value *= factors[i];
    }

    *result = value;
    return 1;
}

static int discard_remaining_input(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];

    while (fgets(buffer, sizeof buffer, stdin) != NULL) {
        if (strchr(buffer, '\n') != NULL) {
            return 1;
        }
    }

    return feof(stdin) && !ferror(stdin);
}

static int read_line(char *buffer, size_t size)
{
    size_t length;

    if (buffer == NULL || size < 2 || size > (size_t)INT_MAX) {
        return 0;
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(buffer);

    if (length > 0 && buffer[length - 1] == '\n') {
        buffer[length - 1] = '\0';
        return 1;
    }

    if (feof(stdin)) {
        return 1;
    }

    if (!discard_remaining_input()) {
        return 0;
    }

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_INPUT_LENGTH + 2];
    char *start;
    char *end;
    uintmax_t parsed;
    uint64_t result;

    if (!read_line(input, sizeof input)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    start = input;
    while (*start != '\0' && isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-' || *start == '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE || parsed > UINT64_MAX) {
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