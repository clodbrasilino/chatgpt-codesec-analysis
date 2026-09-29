#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long cube_sum_even(int n) {
    if (n <= 0 || n > 1000000) {
        return 0;
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

int main(int argc, char * const * const argv) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val <= 0 || val > 1000000) {
        return EXIT_FAILURE;
    }

    long long result = cube_sum_even((int)val);
    if (result == -1) {
        return EXIT_FAILURE;
    }

    if (printf("%lld\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}