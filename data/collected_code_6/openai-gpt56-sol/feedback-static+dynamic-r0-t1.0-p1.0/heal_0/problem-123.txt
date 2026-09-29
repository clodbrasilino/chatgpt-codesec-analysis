#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t sum_proper_divisors(uint64_t number)
{
    uint64_t sum = 1;
    uint64_t divisor;

    if (number <= 1) {
        return 0;
    }

    for (divisor = 2; divisor <= number / divisor; ++divisor) {
        if (number % divisor == 0) {
            uint64_t quotient = number / divisor;

            if (UINT64_MAX - sum < divisor) {
                return UINT64_MAX;
            }
            sum += divisor;

            if (quotient != divisor) {
                if (UINT64_MAX - sum < quotient) {
                    return UINT64_MAX;
                }
                sum += quotient;
            }
        }
    }

    return sum;
}

static int sum_amicable_numbers(uint64_t limit, uint64_t *result)
{
    uint64_t total = 0;
    uint64_t number;

    if (result == NULL) {
        return -1;
    }

    for (number = 2; number <= limit; ++number) {
        uint64_t partner = sum_proper_divisors(number);

        if (partner != UINT64_MAX &&
            partner != number &&
            sum_proper_divisors(partner) == number) {
            if (UINT64_MAX - total < number) {
                return -1;
            }
            total += number;
        }

        if (number == UINT64_MAX) {
            break;
        }
    }

    *result = total;
    return 0;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t parsed;
    uint64_t limit;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <nonnegative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argv[1][0] == '-') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' || parsed > UINT64_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    limit = (uint64_t)parsed;

    if (sum_amicable_numbers(limit, &result) != 0) {
        fprintf(stderr, "Unable to compute result\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}