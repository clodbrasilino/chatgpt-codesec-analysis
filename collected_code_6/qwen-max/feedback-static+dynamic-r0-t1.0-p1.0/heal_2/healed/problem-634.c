#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

int64_t sum_of_fourth_powers(int n) {
    int64_t sum = 0;
    for (int i = 1; i <= n; i++) {
        int64_t term = 2 * (int64_t)i;
        if (term > INT64_MAX / (2 * 2 * 2 * 2)) {
            fprintf(stderr, "Overflow detected.\n");
            exit(EXIT_FAILURE);
        }
        sum += term * term * term * term;
    }
    return sum;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1 || n < 1 || n > 1000) {
        fprintf(stderr, "Invalid input. Please enter a positive integer between 1 and 1000.\n");
        return EXIT_FAILURE;
    }
    int64_t result = sum_of_fourth_powers(n);
    printf("The sum of the fourth powers of the first %d even natural numbers is: %ld\n", n, result);
    return EXIT_SUCCESS;
}