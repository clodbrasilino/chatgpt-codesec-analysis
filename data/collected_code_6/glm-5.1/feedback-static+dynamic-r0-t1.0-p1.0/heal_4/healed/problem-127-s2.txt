#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int multiply(int a, int b) {
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
            if (b < INT_MAX / a) abort();
        }
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