#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int is_valid_triangle(long a, long b, long c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        return 0;
    }
    if (a > LONG_MAX - b || a + b <= c) {
        return 0;
    }
    if (b > LONG_MAX - c || b + c <= a) {
        return 0;
    }
    if (a > LONG_MAX - c || a + c <= b) {
        return 0;
    }
    return 1;
}

int main(void) {
    long a, b, c;
    if (scanf("%ld %ld %ld", &a, &b, &c) != 3) {
        return EXIT_FAILURE;
    }
    if (is_valid_triangle(a, b, c)) {
        printf("True\n");
    } else {
        printf("False\n");
    }
    return EXIT_SUCCESS;
}