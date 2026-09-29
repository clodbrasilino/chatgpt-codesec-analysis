#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int multiply(int a, int b) {
    if (a == 0 || b == 0) {
        return 0;
    }

    if (a == INT_MIN || b == INT_MIN) {
        if (a == INT_MIN && b == INT_MIN) {
            return INT_MIN;
        }
        if (a != INT_MIN && b != INT_MIN) {
            return 0;
        }
        if (a == INT_MIN) {
            if (a < -INT_MAX / b) abort();
            return a * b;
        }
        if (b < -INT_MAX / a) abort();
        return a * b;
    }

    if (a > INT_MAX / b) abort();
    if ((a < 0 && b < 0 && a < INT_MAX / b) || (a < 0 && b > 0 && a < INT_MIN / b) || (a > 0 && b < 0 && b < INT_MIN / a)) {
        abort();
    }

    return a * b;
}

int main(void) {
    int a = 0;
    int b = 0;

    if (scanf("%d", &a) != 1) {
        abort();
    }
    if (scanf("%d", &b) != 1) {
        abort();
    }

    int product = multiply(a, b);
    printf("%d\n", product);

    return 0;
}