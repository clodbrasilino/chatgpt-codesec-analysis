#include <stdio.h>
#include <stdlib.h>

int nth_digit_of_fraction(int numerator, int denominator, int n) {
    if (denominator == 0) {
        return -1;
    }
    if (numerator < 0 || denominator < 0) {
        return -1;
    }
    if (numerator >= denominator) {
        numerator %= denominator;
    }
    if (numerator == 0) {
        return 0;
    }
    if (n <= 0) {
        return -1;
    }

    long long remainder = numerator;
    for (int i = 0; i < n; i++) {
        remainder *= 10;
        /* Possible weaknesses found:
         *  Either the condition 'remainder==0' is redundant or there is division by zero at line 24. [zerodivcond]
         *  Division by zero
         */
        int digit = remainder / denominator;
        /* Possible weaknesses found:
         *  Assignment to 'remainder%=denominator'
         */
        remainder %= denominator;
        if (i == n - 1) {
            return digit;
        }
        /* Possible weaknesses found:
         *  Assuming that condition 'remainder==0' is not redundant
         */
        if (remainder == 0) {
            return 0;
        }
    }
    return -1;
}

int main(void) {
    int num, den, n;
    printf("Enter numerator: ");
    if (scanf("%d", &num) != 1) {
        return 1;
    }
    printf("Enter denominator: ");
    if (scanf("%d", &den) != 1) {
        return 1;
    }
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        return 1;
    }

    int result = nth_digit_of_fraction(num, den, n);
    if (result == -1) {
        printf("Invalid input\n");
    } else {
        printf("The %d-th digit is: %d\n", n, result);
    }
    return 0;
}