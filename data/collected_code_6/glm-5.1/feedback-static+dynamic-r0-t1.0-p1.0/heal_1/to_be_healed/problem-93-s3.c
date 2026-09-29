#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 8, got <no output>
  *  test case 0 failed: expected 81, got <no output>
  *  test case 2 failed: expected 3125, got <no output>
  */

double power(int a, int b) {
    if (b == 0) {
        return 1.0;
    }

    long long abs_b = b;
    if (b < 0) {
        abs_b = -abs_b;
    }

    double result = 1.0;
    double base = a;

    while (abs_b > 0) {
        if (abs_b % 2 == 1) {
            result *= base;
        }
        base *= base;
        abs_b /= 2;
    }

    if (b < 0) {
        if (result == 0.0) {
            exit(EXIT_FAILURE);
        }
        result = 1.0 / result;
    }

    return result;
}

int main(void) {
    int a = 2;
    int b = -3;

    double res = power(a, b);

    printf("%d^%d = %f\n", a, b, res);

    return 0;
}