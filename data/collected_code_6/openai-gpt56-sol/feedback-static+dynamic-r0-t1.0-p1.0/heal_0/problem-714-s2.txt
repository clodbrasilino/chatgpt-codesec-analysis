#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

static size_t count_distinct_prime_factors(uint64_t number)
{
    size_t count = 0;

    if (number < 2) {
        return 0;
    }

    if (number % 2 == 0) {
        ++count;
        do {
            number /= 2;
        } while (number % 2 == 0);
    }

    for (uint64_t factor = 3; factor <= number / factor; factor += 2) {
        if (number % factor == 0) {
            ++count;
            do {
                number /= factor;
            } while (number % factor == 0);
        }
    }

    if (number > 1) {
        ++count;
    }

    return count;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t value;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive-integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        argv[1][0] == '-' || value == 0 || value > UINT64_MAX) {
        fprintf(stderr, "Invalid positive integer\n");
        return EXIT_FAILURE;
    }

    printf("%zu\n", count_distinct_prime_factors((uint64_t)value));
    return EXIT_SUCCESS;
}