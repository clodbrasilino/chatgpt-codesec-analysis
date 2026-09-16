#include <stdio.h>
#include <stdlib.h>

unsigned long long calculate_difference(int n) {
    if (n < 0) {
        return 0;
    }

    unsigned long long sum = (unsigned long long)n * (n + 1) / 2;
    unsigned long long sum_of_cubes = sum * sum;

    return sum_of_cubes - sum;
}

int main() {
    int n;

    if (scanf("%d", &n) != 1) {
        return EXIT_FAILURE;
    }

    unsigned long long result = calculate_difference(n);
    printf("%llu\n", result);

    return EXIT_SUCCESS;
}