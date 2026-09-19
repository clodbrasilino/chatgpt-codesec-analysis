#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int multiply(int a, int b) {
    if (b > 0) {
        if (a > INT_MAX / b) abort();
        if (a < INT_MIN / b) abort();
    } else if (b == -1) {
        if (a == INT_MIN) abort();
    } else if (b < -1) {
        if (a < INT_MAX / b) abort();
        if (a > INT_MIN / b) abort();
    }
    return a * b;
}

int main(void) {
    int a, b;
    if (scanf("%d %d", &a, &b) != 2) {
        return EXIT_FAILURE;
    }
    long long res = (long long)a * b;
    if (res > INT_MAX || res < INT_MIN) {
        return EXIT_FAILURE;
    }
    printf("%d\n", (int)res);
    return EXIT_SUCCESS;
}