#include <stdio.h>
#include <stdlib.h>

long long cube_sum_of_odds(int n) {
    long long sum = 0;
    for (int i = 1, odd = 1; i <= n; ++i, odd += 2) {
        sum += (long long)odd * odd * odd;
    }
    return sum;
}

int main() {
    int n;
    printf("Enter the number of first odd natural numbers to sum cubes: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return EXIT_FAILURE;
    }

    long long result = cube_sum_of_odds(n);
    printf("The cube sum of the first %d odd natural numbers is: %lld\n", n, result);

    return EXIT_SUCCESS;
}