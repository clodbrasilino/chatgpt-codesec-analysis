#include <stdio.h>
#include <stdlib.h>

long long sum_of_squares_even(int n) {
    if (n < 0) {
        fprintf(stderr, "Error: n must be non-negative\n");
        exit(EXIT_FAILURE);
    }
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        long long even = 2LL * i;
        sum += even * even;
    }
    return sum;
}

int main(void) {
    int n;
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }
    long long result = sum_of_squares_even(n);
    printf("%lld\n", result);
    return EXIT_SUCCESS;
}