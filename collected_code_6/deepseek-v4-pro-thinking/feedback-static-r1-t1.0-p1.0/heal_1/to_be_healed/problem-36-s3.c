#include <stdio.h>

int nth_digit(int numerator, int denominator, int n) {
    long long num;
    long long den;
    int i;
    /* Possible weaknesses found:
     *  The scope of the variable 'digit' can be reduced. [variableScope]
     *  Variable 'digit' is assigned a value that is never used. [unreadVariable]
     */
    int digit = 0;

    if (denominator == 0 || n <= 0) {
        return -1;
    }

    num = numerator;
    den = denominator;

    if (num < 0) {
        num = -num;
    }
    if (den < 0) {
        den = -den;
    }

    num %= den;

    for (i = 0; i < n; i++) {
        num *= 10;
        digit = (int)(num / den);
        num %= den;

        if (i == n - 1) {
            return digit;
        }
    }

    return -1;
}

int main(void) {
    int numerator;
    int denominator;
    int n;
    int digit;

    if (scanf("%d %d %d", &numerator, &denominator, &n) != 3) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    digit = nth_digit(numerator, denominator, n);

    if (digit < 0) {
        fprintf(stderr, "Invalid arguments\n");
        return 1;
    }

    printf("%d\n", digit);
    return 0;
}