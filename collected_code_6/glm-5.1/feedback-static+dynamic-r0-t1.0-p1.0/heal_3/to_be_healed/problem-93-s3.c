#include <stdio.h>
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
            return 0.0;
        }
        result = 1.0 / result;
    }

    return result;
}

int main(void) {
    printf("%.0f\n", power(3, 4));
    printf("%.0f\n", power(2, 3));
    printf("%.0f\n", power(5, 5));
    return 0;
}