#include <stdio.h>
#include <stdlib.h>

int find_nth_digit(int numerator, int denominator, int n) {
    if (denominator == 0 || n <= 0) return -1;
    long long remainder = numerator % denominator;
    for (int i = 0; i < n - 1; ++i) {
        remainder = (remainder * 10) % denominator;
    }
    return (remainder * 10) / denominator % 10;
}

int main() {
    int numerator = 1;
    int denominator = 3;
    int n = 5;
    int result = find_nth_digit(numerator, denominator, n);
    printf("The %dth digit of the fraction %d/%d is: %d\n", n, numerator, denominator, result);
    return 0;
}