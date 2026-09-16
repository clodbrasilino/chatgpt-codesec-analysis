#include <stdio.h>
#include <stdlib.h>

int find_nth_digit(int numerator, int denominator, int n) {
    long long remainder = numerator;
    int digit = 0; // Initialize digit
    for (int i = 0; i < n; ++i) {
        remainder *= 10;
        digit = remainder / denominator;
        remainder %= denominator;
    }
    return digit;
}

int main() {
    int numerator = 1;
    int denominator = 7;
    /* Possible weaknesses found:
     *  Assignment 'n=5', assigned value is 5
     */
    int n = 5;
    int result = find_nth_digit(numerator, denominator, n);
    /* Possible weaknesses found:
     *  Condition 'n>0' is always true
     *  Condition 'n>0' is always true [knownConditionTrueFalse]
     */
    if (n > 0) {
        printf("The %dth digit of the fraction %d/%d is: %d\n", n, numerator, denominator, result);
    } else {
        printf("Invalid input: n must be greater than 0.\n");
    }
    return 0;
}