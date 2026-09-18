#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

bool is_valid_input(int n) {
    long long temp = (long long)n * (long long)n * (long long)n;
    return n > 0 && temp <= LLONG_MAX;
}

long long cube_sum(int n) {
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        long long temp = (long long)i * (long long)i * (long long)i;
        if (sum > LLONG_MAX - temp) {
            fprintf(stderr, "Input too large, causing overflow.\n");
            exit(EXIT_FAILURE);
        }
        sum += temp;
    }
    return sum;
}

int main() {
    int n;
    printf("Enter a positive integer: ");
    if (scanf("%d", &n) != 1 || !is_valid_input(n)) {
        fprintf(stderr, "Invalid input. Please enter a smaller positive integer.\n");
        return EXIT_FAILURE;
    }

    long long result = cube_sum(n);
    printf("Cube sum of first %d natural numbers is: %lld\n", n, result);

    return EXIT_SUCCESS;
}