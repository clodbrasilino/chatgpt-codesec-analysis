#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t largest_prime_factor(uint64_t n)
{
    uint64_t largest = 0;

    while (n % UINT64_C(2) == 0) {
        largest = UINT64_C(2);
        n /= UINT64_C(2);
    }

    for (uint64_t factor = UINT64_C(3);
         factor <= n / factor;
         factor += UINT64_C(2)) {
        while (n % factor == 0) {
            largest = factor;
            n /= factor;
        }
    }

    if (n > UINT64_C(1)) {
        largest = n;
    }

    return largest;
}

int main(int argc, const char *const argv[])
{
    char *end = NULL;
    uintmax_t value;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer greater than 1>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE ||
        end == argv[1] ||
        *end != '\0' ||
        value < UINTMAX_C(2) ||
        value > UINT64_MAX) {
        fprintf(stderr,
                "Invalid input: expected an integer from 2 to %" PRIu64 ".\n",
                UINT64_MAX);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", largest_prime_factor((uint64_t)value));

    return EXIT_SUCCESS;
}