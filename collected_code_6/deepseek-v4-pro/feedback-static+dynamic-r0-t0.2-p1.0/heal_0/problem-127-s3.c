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

    unsigned int ua = (unsigned int)abs(a);
    unsigned int ub = (unsigned int)abs(b);

    if (ua > (unsigned int)INT_MAX / ub) {
        fprintf(stderr, "Overflow detected\n");
        exit(EXIT_FAILURE);
    }

    while (ub > 0) {
        if (ub & 1) {
            result += ua;
        }
        ua <<= 1;
        ub >>= 1;
    }

    return negative ? -result : result;
}

int main(void) {
    int a = 12;
    int b = 5;
    int product = multiply(a, b);
    printf("%d * %d = %d\n", a, b, product);

    a = -7;
    b = 6;
    product = multiply(a, b);
    printf("%d * %d = %d\n", a, b, product);

    a = 0;
    b = 42;
    product = multiply(a, b);
    printf("%d * %d = %d\n", a, b, product);

    return 0;
}