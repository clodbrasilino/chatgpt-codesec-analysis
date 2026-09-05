#include <stdio.h>
#include <stdlib.h>

unsigned long long sum_fourth_power_even(int n) {
    if (n <= 0) {
        return 0;
    }

    unsigned long long sum = 0;
    for (int i = 1; i <= n; i++) {
        unsigned long long even = 2ULL * i;
        unsigned long long square = even * even;
        sum += square * square;
    }
    return sum;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n <= 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    unsigned long long result = sum_fourth_power_even(n);
    printf("%llu\n", result);
    return EXIT_SUCCESS;
}