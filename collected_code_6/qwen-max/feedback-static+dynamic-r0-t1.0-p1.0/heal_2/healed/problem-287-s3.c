#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

long sum_of_squares_even(int n) {
    long sum = 0;
    if (n > INT_MAX / 2) return -1; // Check for overflow
    for (int i = 1; i <= n; ++i) {
        if (sum > LONG_MAX - (long)(2 * i) * (2 * i)) return -1; // Check for overflow
        sum += (long)(2 * i) * (2 * i);
    }
    return sum;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }
    long result = sum_of_squares_even(n);
    if (result == -1) {
        printf("Error: Overflow detected.\n");
        return 1;
    }
    printf("The sum of squares of first %d even natural numbers is: %ld\n", n, result);
    return 0;
}