#include <stdio.h>
#include <stdlib.h>

long long sum_even_index_binomial_coefficients(int n) {
    if (n < 0) {
        fprintf(stderr, "Error: n must be non-negative\n");
        exit(EXIT_FAILURE);
    }

    if (n == 0) {
        return 1;
    }

    long long *row = (long long *)malloc((n + 1) * sizeof(long long));
    if (row == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i <= n; i++) {
        row[i] = 0;
    }
    row[0] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = i; j > 0; j--) {
            row[j] += row[j - 1];
        }
    }

    long long sum = 0;
    for (int i = 0; i <= n; i += 2) {
        sum += row[i];
    }

    free(row);
    return sum;
}

int main(void) {
    int test_values[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int num_tests = sizeof(test_values) / sizeof(test_values[0]);

    for (int i = 0; i < num_tests; i++) {
        int n = test_values[i];
        long long result = sum_even_index_binomial_coefficients(n);
        printf("n = %d, sum of even index binomial coefficients = %lld\n", n, result);
    }

    return 0;
}