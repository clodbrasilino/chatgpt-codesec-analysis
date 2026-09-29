#include <stdio.h>
#include <stdlib.h>

long long sum_even_index_binomial_coefficients(int n) {
    if (n < 0) {
        fprintf(stderr, "Error: n must be non-negative\n");
        exit(EXIT_FAILURE);
    }
    /* Possible weaknesses found:
     *  Shifting by a negative value is undefined behaviour [shiftNegative]
     */
    return 1LL << (n - 1);
}

int main(void) {
    int n;
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }
    if (n < 0) {
        fprintf(stderr, "Error: n must be non-negative\n");
        return EXIT_FAILURE;
    }
    printf("Sum of even index binomial coefficients for n = %d: %lld\n", n, sum_even_index_binomial_coefficients(n));
    return EXIT_SUCCESS;
}