#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long cube_sum_even(int n) {
    if (n <= 0) {
        return 0;
    }

    if (n > 1000000) {
        return -1;
    }

    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        long long even = 2LL * i;
        if (even > LLONG_MAX / even) {
            return -1;
        }
        long long square = even * even;
        if (square > LLONG_MAX / even) {
            return -1;
        }
        long long cube = square * even;
        if (sum > LLONG_MAX - cube) {
            return -1;
        }
        sum += cube;
    }

    return sum;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    int n = atoi(argv[1]);
    if (n <= 0) {
        return EXIT_FAILURE;
    }

    long long result = cube_sum_even(n);
    if (result == -1) {
        return EXIT_FAILURE;
    }

    if (printf("%lld\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}