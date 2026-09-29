#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 200, got <no output>
  *  test case 2 failed: expected 32, got <no output>
  *  test case 1 failed: expected 50, got <no output>
  */

int multiply(int a, int b) {
    int result = 0;
    int negative = 0;

    if (b < 0) {
        negative = 1;
        b = -b;
    }

    while (b > 0) {
        if (b & 1) {
            result += a;
        }
        /* Possible weaknesses found:
         *  Shifting a negative value is technically undefined behaviour [shiftNegativeLHS]
         */
        a <<= 1;
        b >>= 1;
    }

    if (negative) {
        result = -result;
    }

    return result;
}

int main() {
    int num1 = 5;
    int num2 = 3;
    int product = multiply(num1, num2);
    printf("%d * %d = %d\n", num1, num2, product);

    num1 = -5;
    num2 = 3;
    product = multiply(num1, num2);
    printf("%d * %d = %d\n", num1, num2, product);

    num1 = 5;
    num2 = -3;
    product = multiply(num1, num2);
    printf("%d * %d = %d\n", num1, num2, product);

    num1 = -5;
    num2 = -3;
    product = multiply(num1, num2);
    printf("%d * %d = %d\n", num1, num2, product);

    return 0;
}