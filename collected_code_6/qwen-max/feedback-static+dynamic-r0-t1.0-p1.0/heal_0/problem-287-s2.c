#include <stdio.h>
#include <stdlib.h>

long long sum_of_squares(int n) {
    if (n < 1) {
        return -1;
    }
    long long sum = 0;
    for (int i = 1; i <= n; ++i) {
        sum += (2 * i) * (2 * i);
    }
    return sum;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input. Please enter an integer.\n");
        return EXIT_FAILURE;
    }
    if (n < 1) {
        fprintf(stderr, "n must be a positive integer.\n");
        return EXIT_FAILURE;
    }
    long long result = sum_of_squares(n);
    printf("Sum of squares of first %d even natural numbers is: %lld\n", n, result);
    return EXIT_SUCCESS;
}