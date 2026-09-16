#include <stdio.h>
#include <stdlib.h>

int is_valid_triangle(int a, int b, int c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        return 0;
    }
    if ((long)a + b <= c) {
        return 0;
    }
    if ((long)a + c <= b) {
        return 0;
    }
    if ((long)b + c <= a) {
        return 0;
    }
    return 1;
}

int main(void) {
    int a, b, c;
    if (scanf("%d %d %d", &a, &b, &c) != 3) {
        return EXIT_FAILURE;
    }
    if (is_valid_triangle(a, b, c)) {
        printf("True\n");
    } else {
        printf("False\n");
    }
    return EXIT_SUCCESS;
}