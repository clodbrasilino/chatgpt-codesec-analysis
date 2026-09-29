#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t largest_prime_factor(uint64_t n)
{
    uint64_t largest = 0;

    while (n % 2 == 0) {
        largest = 2;
        n /= 2;
    }

    for (uint64_t factor = 3; factor <= n / factor; factor += 2) {
        while (n % factor == 0) {
            largest = factor;
            n /= factor;
        }
    }

    if (n > 1) {
        largest = n;
    }

    return largest;
}

int main(int argc, char *const argv[])
{
    char *end = NULL;
    uintmax_t value;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer greater than 1>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        value < UINTMAX_C(2) || value > UINT64_MAX) {
        fprintf(stderr,
                "Invalid input: expected an integer from 2 to %" PRIu64 ".\n",
                UINT64_MAX);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", largest_prime_factor((uint64_t)value));

    return EXIT_SUCCESS;
}