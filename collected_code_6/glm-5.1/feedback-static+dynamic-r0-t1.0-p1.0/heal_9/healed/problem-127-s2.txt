#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long safe_multiply(int a, int b) {
    if (a > 0) {
        if (b > 0) {
            if (a > INT_MAX / b) abort();
        } else if (b < 0) {
            if (b < INT_MIN / a) abort();
        }
    } else if (a < 0) {
        if (b > 0) {
            if (a < INT_MIN / b) abort();
        } else if (b < 0) {
            if (a < INT_MAX / b) abort();
        }
    }
    long long res = (long long)a * (long long)b;
    if (res < INT_MIN || res > INT_MAX) {
        abort();
    }
    return res;
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

    int product = (int)safe_multiply(a, b);
    printf("%d\n", product);

    return 0;
}