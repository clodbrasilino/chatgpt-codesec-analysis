#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long cube_sum_of_odds(int n) {
    if (n < 0 || n > INT_MAX / 2) {
        return -1;
    }
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        int odd_number = 2 * i - 1;
        long long cube = (long long)odd_number * odd_number * odd_number;
        if (sum > LLONG_MAX - cube) {
            return -1;
        }
        sum += cube;
    }
    return sum;
}

int main() {
    int n;
    printf("Enter the number of first odd natural numbers: ");
    if (scanf("%d", &n) != 1 || n < 0) {
        fprintf(stderr, "Invalid input. Please enter a non-negative integer.\n");
        return EXIT_FAILURE;
    }

    long long result = cube_sum_of_odds(n);
    if (result == -1) {
        fprintf(stderr, "Calculation overflow or invalid input.\n");
        return EXIT_FAILURE;
    }

    printf("The cube sum of the first %d odd natural numbers is: %lld\n", n, result);

    return EXIT_SUCCESS;
}