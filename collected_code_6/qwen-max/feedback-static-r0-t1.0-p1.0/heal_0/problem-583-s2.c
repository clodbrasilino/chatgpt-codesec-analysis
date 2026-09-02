#include <stdio.h>
#include <stdlib.h>

unsigned long long binomial_coefficient(int n, int k) {
    unsigned long long res = 1;
    if (k > n - k) k = n - k;
    for (int i = 0; i < k; ++i) {
        res *= (n - i);
        res /= (i + 1);
    }
    return res;
}

unsigned long long catalan_number(int n) {
    if (n <= 1) return 1;
    return binomial_coefficient(2 * n, n) / (n + 1);
}

int main() {
    int n;
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Input is not an integer.\n");
        return EXIT_FAILURE;
    }
    if (n < 0) {
        printf("Please enter a non-negative integer.\n");
        return EXIT_FAILURE;
    }

    unsigned long long result = catalan_number(n);
    printf("The %dth Catalan number is: %llu\n", n, result);

    return 0;
}