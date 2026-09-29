#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t smallest_prime_divisor(uint64_t number)
{
    uint64_t divisor;

    if (number < 2U) {
        return 0U;
    }

    if (number % 2U == 0U) {
        return 2U;
    }

    for (divisor = 3U; divisor <= number / divisor; divisor += 2U) {
        if (number % divisor == 0U) {
            return divisor;
        }
    }

    return number;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t parsed;
    uint64_t number;
    uint64_t divisor;

    if (argc != 2) {
        (void)fprintf(stderr, "Usage: %s <integer greater than 1>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        argv[1][0] == '-' || parsed > UINT64_MAX || parsed < 2U) {
        (void)fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    number = (uint64_t)parsed;
    divisor = smallest_prime_divisor(number);

    if (printf("%" PRIu64 "\n", divisor) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}