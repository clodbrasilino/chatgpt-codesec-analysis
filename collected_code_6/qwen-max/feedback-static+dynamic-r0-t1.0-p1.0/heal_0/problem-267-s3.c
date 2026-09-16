#include <stdio.h>

long long sum_of_squares(long n) {
    long long sum = 0;
    for (long i = 1; i <= 2 * n - 1; i += 2) {
        sum += i * i;
    }
    return sum;
}

int main() {
    long n;
    printf("Enter the value of n: ");
    if (scanf("%ld", &n) != 1 || n < 1) {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return 1;
    }
    long long result = sum_of_squares(n);
    printf("The sum of squares of the first %ld odd natural numbers is: %lld\n", n, result);
    return 0;
}