#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 5, got 0
  *  test case 1 failed: expected 6, got 0
  */

int find_nth_digit(int numerator, int denominator, int n) {
    if (denominator == 0 || n <= 0) return -1;
    long long remainder = numerator % denominator;
    for (int i = 0; i < n; ++i) {
        remainder *= 10;
        /* Possible weaknesses found:
         *  Value stored to 'digit' during its initialization is never read [deadcode.DeadStores]
         *  Variable 'digit' is assigned a value that is never used. [unreadVariable]
         */
        int digit = remainder / denominator;
        remainder %= denominator;
    }
    return remainder * 10 / denominator;
}

int main() {
    int numerator = 1;
    int denominator = 3;
    int n = 5;
    int result = find_nth_digit(numerator, denominator, n);
    printf("The %dth digit of the fraction %d/%d is: %d\n", n, numerator, denominator, result);
    return 0;
}