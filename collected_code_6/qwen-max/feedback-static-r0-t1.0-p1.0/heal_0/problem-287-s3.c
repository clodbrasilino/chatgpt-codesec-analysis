#include <stdio.h>

long sum_of_squares_even(int n) {
    long sum = 0;
    for (int i = 1; i <= n; ++i) {
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
    printf("The sum of squares of first %d even natural numbers is: %ld\n", n, result);
    return 0;
}