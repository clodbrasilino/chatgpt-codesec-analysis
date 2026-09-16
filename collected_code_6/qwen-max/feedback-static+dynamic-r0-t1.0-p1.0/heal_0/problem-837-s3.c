#include <stdio.h>
#include <stdlib.h>

long long cube_sum_of_odds(int n) {
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        int odd_number = 2 * i - 1;
        sum += (long long)odd_number * odd_number * odd_number;
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
    printf("The cube sum of the first %d odd natural numbers is: %lld\n", n, result);

    return EXIT_SUCCESS;
}