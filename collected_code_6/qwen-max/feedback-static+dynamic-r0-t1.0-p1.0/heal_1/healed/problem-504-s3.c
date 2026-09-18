#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

bool is_valid_input(int n) {
    return n > 0 && (long long)n * n * n <= LLONG_MAX;
}

long long cube_sum(int n) {
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        if (!is_valid_input(i)) {
            fprintf(stderr, "Input too large, causing overflow.\n");
            exit(EXIT_FAILURE);
        }
        sum += (long long)i * i * i;
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