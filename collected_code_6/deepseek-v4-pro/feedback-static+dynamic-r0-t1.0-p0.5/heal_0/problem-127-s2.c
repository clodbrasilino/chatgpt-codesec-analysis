#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int multiply(int a, int b) {
    int result = 0;
    int negative = 0;

    if (a == 0 || b == 0) {
        return 0;
    }

    if ((a < 0 && b > 0) || (a > 0 && b < 0)) {
        negative = 1;
    }

    unsigned int ua = (unsigned int)(a < 0 ? -a : a);
    unsigned int ub = (unsigned int)(b < 0 ? -b : b);

    if (ua > (unsigned int)INT_MAX && ub > 1) {
        return 0;
    }
    if (ub > (unsigned int)INT_MAX && ua > 1) {
        return 0;
    }

    while (ub > 0) {
        if (ub & 1) {
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
    b = 10;
    printf("%d * %d = %d\n", a, b, multiply(a, b));

    a = -3;
    b = -3;
    printf("%d * %d = %d\n", a, b, multiply(a, b));

    return 0;
}