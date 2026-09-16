#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

static bool is_non_prime(unsigned long long number)
{
    if (number < 2U) {
        return true;
    }

    for (unsigned long long divisor = 2U; divisor <= number / divisor; ++divisor) {
        if (number % divisor == 0U) {
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
        fprintf(stderr, "Invalid non-negative integer: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    printf("%llu is %snon-prime.\n", number, is_non_prime(number) ? "" : "not ");

    if (fflush(stdout) == EOF) {
        fprintf(stderr, "Failed to write output.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}