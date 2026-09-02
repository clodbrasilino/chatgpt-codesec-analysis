#include <stdio.h>
#include <stdlib.h>

int find_nth_digit(int numerator, int denominator, int n) {
    if (denominator == 0 || n <= 0) return -1;
    long long result = numerator;
    for (int i = 1; i < n; ++i) {
        result = (result * 10) % denominator;
    }
    return (int)((result * 10) / denominator);
}

int main() {
    int numerator = 1;
    int denominator = 7;
    int n = 5;
    int nth_digit = find_nth_digit(numerator, denominator, n);
    if (nth_digit != -1) {
        printf("The %dth digit is: %d\n", n, nth_digit);
    } else {
        printf("Invalid input or calculation error.\n");
    }
    return 0;
}