#include <stdio.h>
#include <stdlib.h>

unsigned long long sum_fourth_power_even(int n) {
    if (n <= 0) {
        return 0;
    }

    unsigned long long sum = 0;
    for (int i = 1; i <= n; i++) {
        unsigned long long even = 2ULL * i;
        sum += even * even * even * even;
    }
    return sum;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    long val = strtol(argv[1], NULL, 10);
    if (val <= 0 || val > 10000) {
        return EXIT_FAILURE;
    }

    unsigned long long result = sum_fourth_power_even((int)val);
    printf("%llu\n", result);

    return EXIT_SUCCESS;
}