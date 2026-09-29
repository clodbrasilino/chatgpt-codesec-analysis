#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_of_divisors(uint64_t number, uint64_t *sum)
{
    uint64_t divisor;
    uint64_t result = 0;

    if (number == 0 || sum == NULL) {
        return 0;
    }

    for (divisor = 1; divisor <= number / divisor; ++divisor) {
        if (number % divisor == 0) {
            uint64_t paired_divisor = number / divisor;

            if (UINT64_MAX - result < divisor) {
                return 0;
            }
            result += divisor;

            if (paired_divisor != divisor) {
                if (UINT64_MAX - result < paired_divisor) {
                    return 0;
                }
                result += paired_divisor;
            }
        }
    }

    *sum = result;
    return 1;
}

int main(void)
{
    char input[128];
    char *end;
    uintmax_t parsed;
    uint64_t number;
    uint64_t sum;

    if (printf("Enter a positive integer: ") < 0) {
        return EXIT_FAILURE;
    }

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    if (fgets(input, sizeof input, stdin) == NULL) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (input[0] == '\0') {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    end = input;
    parsed = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input || parsed == 0 || parsed > UINT64_MAX) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\n' || *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0') {
        fprintf(stderr, "Unexpected input.\n");
        return EXIT_FAILURE;
    }

    if (input[sizeof input - 2] != '\n') {
        int ch = getchar();

        if (ch != '\n' && ch != EOF) {
            while (ch != '\n' && ch != EOF) {
                ch = getchar();
            }
            fprintf(stderr, "Unexpected input.\n");
            return EXIT_FAILURE;
        }
    }

    number = (uint64_t)parsed;

    if (!sum_of_divisors(number, &sum)) {
        fprintf(stderr, "Unable to calculate the sum.\n");
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}