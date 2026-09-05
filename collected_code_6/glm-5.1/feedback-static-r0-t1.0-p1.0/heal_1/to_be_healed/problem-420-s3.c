#include <stdio.h>
#include <stdlib.h>

long long cube_sum_even(int n) {
    if (n <= 0) {
        return 0;
    }

    if (n > 1000000) {
        return -1;
    }

    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        long long even = 2 * i;
        /* Possible weaknesses found:
         *  '__LLONG_MAX__' undeclared (first use in this function)
         *  each undeclared identifier is reported only once for each function it appears in
         *  use of undeclared identifier '__LLONG_MAX__'
         */
        if (even > __LLONG_MAX__ / even) {
            return -1;
        }
        long long square = even * even;
        /* Possible weaknesses found:
         *  use of undeclared identifier '__LLONG_MAX__'
         */
        if (square > __LLONG_MAX__ / even) {
            return -1;
        }
        long long cube = square * even;
        /* Possible weaknesses found:
         *  use of undeclared identifier '__LLONG_MAX__'
         */
        if (sum > __LLONG_MAX__ - cube) {
            return -1;
        }
        sum += cube;
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