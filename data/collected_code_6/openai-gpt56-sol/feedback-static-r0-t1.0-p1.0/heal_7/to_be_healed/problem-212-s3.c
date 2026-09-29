#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT_LENGTH 64
#define MAX_N UINT64_C(4934)

static int sum_fourth_powers(uint64_t n, uint64_t *result)
{
    uint64_t factors[4];
    uint64_t divisor = UINT64_C(30);
    uint64_t value = UINT64_C(1);

    if (result == NULL || n == 0 || n > MAX_N) {
        return 0;
    }

    factors[0] = n;
    factors[1] = n + UINT64_C(1);
    factors[2] = UINT64_C(2) * n + UINT64_C(1);
    factors[3] = UINT64_C(3) * n * n + UINT64_C(3) * n - UINT64_C(1);

    for (size_t i = 0; i < 4 && divisor > 1; ++i) {
        for (uint64_t candidate = 2; candidate <= divisor; ++candidate) {
            while (divisor % candidate == 0 &&
                   factors[i] % candidate == 0) {
                divisor /= candidate;
                factors[i] /= candidate;
            }
        }
    }

    if (divisor != 1) {
        return 0;
    }

    for (size_t i = 0; i < 4; ++i) {
        if (factors[i] != 0 && value > UINT64_MAX / factors[i]) {
            return 0;
        }
        value *= factors[i];
    }

    *result = value;
    return 1;
}

static int read_line(char *buffer, size_t size)
{
    size_t length;

    if (buffer == NULL || size < 2) {
        return 0;
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return 0;
    }

    length = 0;
    while (length < size && buffer[length] != '\0' &&
           buffer[length] != '\n') {
        ++length;
    }

    if (length < size && buffer[length] == '\n') {
        buffer[length] = '\0';
        return 1;
    }

    if (length == size || buffer[length] != '\0') {
        return 0;
    }

    if (!feof(stdin)) {
        int ch;

        do {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        return 0;
    }

    return length != 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_INPUT_LENGTH];
    char *end;
    uintmax_t parsed;
    uint64_t result;

    if (printf("Enter n: ") < 0 || fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    if (!read_line(input, sizeof input)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(input, &end, 10);

    if (end == input || errno == ERANGE) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0' || parsed == 0 || parsed > UINTMAX_C(4934)) {
        fputs("Input is out of the supported range\n", stderr);
        return EXIT_FAILURE;
    }

    if (!sum_fourth_powers((uint64_t)parsed, &result)) {
        fputs("Input is out of the supported range\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Sum: %" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}