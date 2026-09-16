#include <stdio.h>
#include <stdlib.h>

int find_nth_digit(int numerator, int denominator, int n) {
    long long remainder = numerator;
    for (int i = 0; i < n; ++i) {
        if (remainder == 0) return 0;
        remainder *= 10;
        remainder %= denominator;
    }
    return (int)(remainder * 10 / denominator) % 10;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);
    if (n > 0) {
        int numerator = 1, denominator = 7;
        int result = find_nth_digit(numerator, denominator, n);
        printf("The %dth digit of the fraction %d/%d is: %d\n", n, numerator, denominator, result);
    } else {
        printf("Invalid input: n must be greater than 0.\n");
    }
    return 0;
}