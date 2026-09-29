#include <stdio.h>
#include <stdlib.h>

long long calculate_difference(int n) {
    if (n < 0 || n > 77935) {
        return -1;
    }

    long long sum_n = (long long)n * (n + 1) / 2;
    long long sum_cubes = sum_n * sum_n;

    return sum_cubes - sum_n;
}

int main(void) {
    int n;
    
    if (scanf("%d", &n) != 1) {
        return EXIT_FAILURE;
    }

    if (n < 0) {
        return EXIT_FAILURE;
    }

    long long result = calculate_difference(n);
    if (result == -1 && n != 0 && n != 1) {
        return EXIT_FAILURE;
    }
    
    printf("%lld\n", result);

    return EXIT_SUCCESS;
}