#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int multiply(int a, int b) {
    long long result = 0;
    long long la = a;
    long long lb = b;
    int sign = 1;

    if (la < 0) {
        sign = -sign;
        la = -la;
    }

    if (lb < 0) {
        sign = -sign;
        lb = -lb;
    }

    while (lb > 0) {
        if (lb & 1) {
            result += la;
        }
        la <<= 1;
        lb >>= 1;
    }

    if (sign < 0) {
        result = -result;
    }

    if (result > INT_MAX || result < INT_MIN) {
        exit(EXIT_FAILURE);
    }

    return (int)result;
}

int main(void) {
    int a = 0;
    int b = 0;

    if (scanf("%d %d", &a, &b) != 2) {
        return EXIT_FAILURE;
    }

    int res = multiply(a, b);
    printf("%d\n", res);

    return EXIT_SUCCESS;
}