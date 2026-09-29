#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_even_factors(uint64_t number, uint64_t *sum)
{
    uint64_t total = 0;

    if (number == 0 || sum == NULL) {
        return 0;
    }

    for (uint64_t divisor = 1; divisor <= number / divisor; ++divisor) {
        if (number % divisor != 0) {
            continue;
        }

        uint64_t quotient = number / divisor;

        if ((divisor & UINT64_C(1)) == 0) {
            if (UINT64_MAX - total < divisor) {
                return 0;
            }
            total += divisor;
        }

        if (quotient != divisor && (quotient & UINT64_C(1)) == 0) {
            if (UINT64_MAX - total < quotient) {
                return 0;
            }
            total += quotient;
        }
    }

    *sum = total;
    return 1;
}

int main(void)
{
    char input[128];
    char *end;
    uintmax_t parsed;
    uint64_t sum;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        int ch;

        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        fputs("Invalid positive integer.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input || parsed == 0 ||
        parsed > UINT64_MAX || input[0] == '-') {
        fputs("Invalid positive integer.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid positive integer.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!sum_even_factors((uint64_t)parsed, &sum)) {
        fputs("Unable to calculate the sum.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}