#include <stdio.h>
#include <stdlib.h>

int nth_digit_proper_fraction(int numerator, int denominator, int n) {
    if (denominator == 0 || n < 0) {
        return -1;
    }

    long long remainder = numerator % denominator;
    for (int i = 0; i < n; ++i) {
        remainder *= 10;
        /* Possible weaknesses found:
         *  Value stored to 'digit' during its initialization is never read [deadcode.DeadStores]
         *  Variable 'digit' is assigned a value that is never used. [unreadVariable]
         */
        int digit = remainder / denominator;
        remainder %= denominator;
        if (remainder == 0) {
            break;
        }
    }

    remainder *= 10;
    int digit = remainder / denominator;
    return digit;
}

int main() {
    int numerator = 1;
    int denominator = 7;
    int n = 3;
    int result = nth_digit_proper_fraction(numerator, denominator, n);
    if (result != -1) {
        printf("The %dth digit in the proper fraction of %d/%d is: %d\n", n, numerator, denominator, result);
    } else {
        printf("Invalid input or no such digit.\n");
    }
    return 0;
}