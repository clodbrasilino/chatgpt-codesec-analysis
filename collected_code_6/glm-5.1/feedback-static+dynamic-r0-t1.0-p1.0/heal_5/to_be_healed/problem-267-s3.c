#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

unsigned long long sum_of_squares_of_odds(unsigned int n) {
    unsigned long long max_n = (unsigned long long)((1ULL << 63) - 1) / 4ULL;
    if (n > max_n) {
        return 0;
    }
    return (unsigned long long)n * (2ULL * n - 1ULL) * (2ULL * n + 1ULL) / 3ULL;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    char *endptr;
    errno = 0;
    unsigned long long val = strtoull(argv[1], &endptr, 10);

    if (*endptr != '\0' || errno != 0 || val == 0 || val > 0xFFFFFFFFULL) {
        return EXIT_FAILURE;
    }

    unsigned int n = (unsigned int)val;

    unsigned long long result = sum_of_squares_of_odds(n);

    if (result == 0) {
        return EXIT_FAILURE;
    }

    printf("%llu\n", result);

    return EXIT_SUCCESS;
}