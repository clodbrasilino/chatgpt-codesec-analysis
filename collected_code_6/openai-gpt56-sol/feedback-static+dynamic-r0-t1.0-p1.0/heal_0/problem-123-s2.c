#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t sum_proper_divisors(uint64_t number)
{
    uint64_t sum;
    uint64_t divisor;

    if (number <= 1U) {
        return 0U;
    }

    sum = 1U;

    for (divisor = 2U; divisor <= number / divisor; ++divisor) {
        if (number % divisor == 0U) {
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
    uint64_t total = 0U;
    uint64_t number;

    if (result == NULL) {
        return 0;
    }

    for (number = 2U; number <= limit; ++number) {
        uint64_t partner = sum_proper_divisors(number);

        if (partner != UINT64_MAX &&
            partner != number &&
            partner > 1U &&
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
    uintmax_t parsed;
    uint64_t limit;
    uint64_t result;

    if (argc != 2) {
        (void)fprintf(stderr, "Usage: %s <nonnegative-limit>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argv[1][0] == '-') {
        (void)fprintf(stderr, "Invalid limit\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE ||
        end == argv[1] ||
        *end != '\0' ||
        parsed > UINT64_MAX) {
        (void)fprintf(stderr, "Invalid limit\n");
        return EXIT_FAILURE;
    }

    limit = (uint64_t)parsed;

    if (!sum_amicable_numbers(limit, &result)) {
        (void)fprintf(stderr, "Unable to compute the sum\n");
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}