#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_fourth_powers(uint64_t n, uint64_t *result)
{
    uint64_t factors[4];
    uint64_t divisor = 30U;
    uint64_t value = 1U;
    size_t i;

    if (result == NULL) {
        return 0;
    }

    factors[0] = n;
    factors[1] = n + 1U;
    factors[2] = 2U * n + 1U;
    factors[3] = 3U * n * n + 3U * n - 1U;

    for (i = 0U; i < 4U && divisor > 1U; ++i) {
        uint64_t candidate;

        for (candidate = 2U; candidate <= divisor; ++candidate) {
            while (divisor % candidate == 0U &&
                   factors[i] % candidate == 0U) {
                divisor /= candidate;
                factors[i] /= candidate;
            }
        }
    }

    if (divisor != 1U) {
        return 0;
    }

    for (i = 0U; i < 4U; ++i) {
        if (factors[i] != 0U && value > UINT64_MAX / factors[i]) {
            return 0;
        }
        value *= factors[i];
    }

    *result = value;
    return 1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    char *end;
    uintmax_t parsed;
    uint64_t result;
    size_t length;
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;

    if (printf("Enter n: ") < 0 || fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    if (fgets(input, sizeof input, stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    length = 0U;
    while (length < sizeof input && input[length] != '\0' &&
           input[length] != '\n') {
        ++length;
    }

    if (length == sizeof input) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (input[length] != '\n') {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
        if (ch != '\n' && ch != EOF) {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
            }
            fprintf(stderr, "Invalid input\n");
            return EXIT_FAILURE;
        }
    }

    errno = 0;
    end = input;
    parsed = strtoumax(input, &end, 10);

    if (end == input || errno == ERANGE || parsed > UINT64_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    while (*end != '\0' && *end != '\n' &&
           isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' && *end != '\n') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (parsed == 0U || parsed > 4934U ||
        !sum_fourth_powers((uint64_t)parsed, &result)) {
        fprintf(stderr, "Input is out of the supported range\n");
        return EXIT_FAILURE;
    }

    if (printf("Sum: %" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}