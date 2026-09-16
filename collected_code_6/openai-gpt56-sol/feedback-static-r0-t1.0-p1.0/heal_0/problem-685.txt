#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

static int is_prime(uint64_t number)
{
    if (number < 2U) {
        return 0;
    }

    if (number == 2U) {
        return 1;
    }

    if (number % 2U == 0U) {
        return 0;
    }

    for (uint64_t divisor = 3U; divisor <= number / divisor; divisor += 2U) {
        if (number % divisor == 0U) {
            return 0;
        }
    }

    return 1;
}

static int sum_primes(uint64_t limit, uint64_t *sum)
{
    uint64_t total = 0U;

    if (sum == NULL) {
        return 0;
    }

    for (uint64_t number = 2U; number <= limit; ++number) {
        if (is_prime(number)) {
            if (UINT64_MAX - total < number) {
                return 0;
            }
            total += number;
        }
    }

    *sum = total;
    return 1;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t parsed_value;
    uint64_t sum;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <non-negative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed_value = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        argv[1][0] == '-' || parsed_value > UINT64_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!sum_primes((uint64_t)parsed_value, &sum)) {
        fputs("Sum overflow\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}