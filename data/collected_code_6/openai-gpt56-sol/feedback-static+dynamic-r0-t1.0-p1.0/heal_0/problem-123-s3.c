#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t sum_proper_divisors(uint64_t n)
{
    uint64_t sum = 1;

    if (n <= 1) {
        return 0;
    }

    for (uint64_t divisor = 2; divisor <= n / divisor; ++divisor) {
        if (n % divisor == 0) {
            uint64_t quotient = n / divisor;

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

    if (result == NULL) {
        return 0;
    }

    for (uint64_t number = 2; number <= limit; ++number) {
        uint64_t partner = sum_proper_divisors(number);

        if (partner != UINT64_MAX &&
            partner != number &&
            sum_proper_divisors(partner) == number) {
            if (UINT64_MAX - total < number) {
                return 0;
            }
            total += number;
        }

        if (number == UINT64_MAX) {
            break;
        }
    }

    *result = total;
    return 1;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t parsed_limit;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <nonnegative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed_limit = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE ||
        end == argv[1] ||
        *end != '\0' ||
        argv[1][0] == '-' ||
        parsed_limit > UINT64_MAX) {
        fprintf(stderr, "Invalid limit\n");
        return EXIT_FAILURE;
    }

    if (!sum_amicable_numbers((uint64_t)parsed_limit, &result)) {
        fprintf(stderr, "Unable to calculate the sum\n");
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}