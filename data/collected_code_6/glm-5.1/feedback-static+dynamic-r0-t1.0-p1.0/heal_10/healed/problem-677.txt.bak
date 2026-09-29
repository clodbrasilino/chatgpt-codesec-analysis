#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int is_valid_triangle(long a, long b, long c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        return 0;
    }
    if (b > LONG_MAX - a || c > LONG_MAX - a) {
        return 1;
    }
    if (a > b + c || b > a + c || c > a + b) {
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