#include <stdio.h>
#include <stdlib.h>

int is_isosceles(int a, int b, int c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        return 0;
    }
    if (a + b <= c || a + c <= b || b + c <= a) {
        return 0;
    }
    if (a == b || b == c || a == c) {
        return 1;
    }
    return 0;
}

int main(void) {
    int a, b, c;
    if (scanf("%d %d %d", &a, &b, &c) != 3) {
        return EXIT_FAILURE;
    }
    if (is_isosceles(a, b, c)) {
        printf("Isosceles\n");
    } else {
        printf("Not Isosceles\n");
    }
    return EXIT_SUCCESS;
}