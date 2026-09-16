#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

unsigned long long cube_sum_even(int n) {
    if (n <= 0) {
        return 0;
    }

    if (n > 2642245) {
        return 0;
    }

    unsigned long long sum = 0;
    unsigned long long i;

    for (i = 1; i <= (unsigned long long)n; i++) {
        unsigned long long even_num = 2 * i;
        unsigned long long term = even_num * even_num;

        if (term > ULLONG_MAX / even_num) {
            return 0;
        }

        unsigned long long cube = term * even_num;

        if (sum > ULLONG_MAX - cube) {
            return 0;
        }
        
        sum += cube;
    }

    return sum;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    int n;

    if (argc != 2) {
        return EXIT_FAILURE;
    }

    errno = 0;
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);

    if (errno != 0 || endptr == argv[1] || *endptr != '\0' || val < 0 || val > INT_MAX) {
        return EXIT_FAILURE;
    }

    n = (int)val;

    unsigned long long result = cube_sum_even(n);

    printf("%llu\n", result);

    return EXIT_SUCCESS;
}