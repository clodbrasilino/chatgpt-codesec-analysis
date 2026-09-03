#include <stdio.h>
#include <limits.h>
#include <stdint.h>

int multiply(int a, int b) {
    int result = 0;
    int negative = 0;

    if (a == 0 || b == 0) {
        return 0;
    }

    if ((a < 0 && b > 0) || (a > 0 && b < 0)) {
        negative = 1;
    }

    unsigned int ua = (unsigned int)(a < 0 ? -(unsigned int)a : (unsigned int)a);
    unsigned int ub = (unsigned int)(b < 0 ? -(unsigned int)b : (unsigned int)b);

    if (ub != 0 && ua > (unsigned int)INT_MAX / ub) {
        return 0;
    }

    while (ub > 0) {
        if (ub & 1U) {
            result += (int)ua;
        }
        ua <<= 1;
        ub >>= 1;
    }

    return negative ? -result : result;
}

int main(void) {
    int a = 7;
    int b = 6;
    printf("%d * %d = %d\n", a, b, multiply(a, b));

    a = -5;
    b = 4;
    printf("%d * %d = %d\n", a, b, multiply(a, b));

    a = 0;
    b = 100;
    printf("%d * %d = %d\n", a, b, multiply(a, b));

    a = INT_MAX;
    b = 2;
    printf("%d * %d = %d\n", a, b, multiply(a, b));

    return 0;
}