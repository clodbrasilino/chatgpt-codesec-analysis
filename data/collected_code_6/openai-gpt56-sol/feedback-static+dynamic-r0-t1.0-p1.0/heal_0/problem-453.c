#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_even_factors(uint64_t number, uint64_t *sum)
{
    uint64_t total = 0;

    if (number == 0 || sum == NULL) {
        return -1;
    }

    for (uint64_t factor = 1; factor <= number / factor; ++factor) {
        if (number % factor == 0) {
            uint64_t paired_factor = number / factor;

            if ((factor % 2U) == 0U) {
                if (UINT64_MAX - total < factor) {
                    return -1;
                }
                total += factor;
            }

            if (paired_factor != factor && (paired_factor % 2U) == 0U) {
                if (UINT64_MAX - total < paired_factor) {
                    return -1;
                }
                total += paired_factor;
            }
        }
    }

    *sum = total;
    return 0;
}

int main(void)
{
    char input[128];
    char *end = NULL;
    uintmax_t parsed_number;
    uint64_t number;
    uint64_t sum;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed_number = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input || parsed_number == 0 ||
        parsed_number > UINT64_MAX) {
        fputs("Invalid number.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t') {
        ++end;
    }

    if (*end != '\n' && *end != '\0') {
        fputs("Invalid number.\n", stderr);
        return EXIT_FAILURE;
    }

    number = (uint64_t)parsed_number;

    if (sum_even_factors(number, &sum) != 0) {
        fputs("Unable to calculate the sum.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}