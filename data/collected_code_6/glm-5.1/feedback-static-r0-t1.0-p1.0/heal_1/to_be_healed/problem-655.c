#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

unsigned long long sum_of_fifth_powers(unsigned int n) {
    unsigned long long sum = 0;
    for (unsigned int i = 1; i <= n; ++i) {
        unsigned long long term = (unsigned long long)i * i * i * i * i;
        if (sum > ULLONG_MAX - term) {
            errno = ERANGE;
            return 0;
        }
        sum += term;
    }
    return sum;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    char *endptr;
    errno = 0;
    unsigned long long val = strtoull(argv[1], &endptr, 10);

    if (errno != 0 || *endptr != '\0' || val > UINT_MAX) {
        return EXIT_FAILURE;
    }

    unsigned int n = (unsigned int)val;
    errno = 0;
    unsigned long long result = sum_of_fifth_powers(n);

    if (errno == ERANGE) {
        return EXIT_FAILURE;
    }

    printf("%llu\n", result);

    return EXIT_SUCCESS;
}