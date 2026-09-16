#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_non_prime(unsigned long long number)
{
    if (number < 2ULL) {
        return true;
    }

    for (unsigned long long divisor = 2ULL;
         divisor <= number / divisor;
         ++divisor) {
        if (number % divisor == 0ULL) {
            return true;
        }
    }

    return false;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    unsigned long long number;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <non-negative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoull(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' || argv[1][0] == '-') {
        fprintf(stderr, "Invalid non-negative integer.\n");
        return EXIT_FAILURE;
    }

    if (is_non_prime(number)) {
        printf("%llu is not prime.\n", number);
    } else {
        printf("%llu is prime.\n", number);
    }

    return EXIT_SUCCESS;
}