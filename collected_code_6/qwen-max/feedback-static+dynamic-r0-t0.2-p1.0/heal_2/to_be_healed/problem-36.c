#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 3, got 9
  *  test case 0 failed: expected 5, got 0
  *  test case 1 failed: expected 6, got 0
  */

int find_nth_digit(int numerator, int denominator, int n) {
    if (denominator == 0 || n <= 0) return -1;
    long long result = 0;
    for (int i = 0; i < n - 1; ++i) {
        result = (result * 10 + numerator) % denominator;
    }
    result = (result * 10 + numerator) / denominator;
    return (int)(result % 10);
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