#include <stdio.h>
#include <stdlib.h>

long long sum_fourth_power_odd(int n) {
    if (n <= 0) {
        return 0;
    }

    long long sum = 0;

    for (int i = 1; i <= n; ++i) {
        long long term = (2LL * i) - 1LL;
        term = term * term;
        sum += term * term;
    }

    return sum;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long val = strtol(argv[1], &endptr, 10);

    if (endptr == argv[1] || *endptr != '\0' || val <= 0 || val > 2147483647) {
        fprintf(stderr, "Error: n must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    int n = (int)val;
    long long result = sum_fourth_power_odd(n);

    printf("%lld\n", result);

    return EXIT_SUCCESS;
}