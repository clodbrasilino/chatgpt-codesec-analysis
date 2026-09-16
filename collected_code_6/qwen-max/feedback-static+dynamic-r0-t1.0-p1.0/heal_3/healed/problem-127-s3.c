#include <stdio.h>
#include <limits.h>

int multiply(int a, int b) {
    int result = 0;
    int negative = 0;

    if (b < 0) {
        negative = 1;
        b = -b;
    }

    while (b > 0) {
        if (b & 1) {
            if ((result > 0 && a > INT_MAX - result) || (result < 0 && a < INT_MIN - result)) {
                return 0;
            }
            result += a;
        }
        if (a > INT_MAX / 2 || a < INT_MIN / 2) {
            break;
        }
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

    num1 = 20;
    num2 = 10;
    product = multiply(num1, num2);
    printf("%d * %d = %d\n", num1, num2, product);

    num1 = 20;
    num2 = -2;
    product = multiply(num1, num2);
    printf("%d * %d = %d\n", num1, num2, product);

    num1 = 10;
    num2 = 3;
    product = multiply(num1, num2);
    printf("%d * %d = %d\n", num1, num2, product);

    num1 = 200;
    num2 = 1;
    product = multiply(num1, num2);
    printf("%d * %d = %d\n", num1, num2, product);

    return 0;
}