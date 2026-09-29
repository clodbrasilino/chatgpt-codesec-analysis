#include <stdio.h>
#include <stdlib.h>

int is_valid_triangle(int a, int b, int c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        return 0;
    }
    if ((long)a + (long)b <= (long)c) {
        return 0;
    }
    if ((long)b + (long)c <= (long)a) {
        return 0;
    }
    if ((long)a + (long)c <= (long)b) {
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
        printf("Valid\n");
    } else {
        printf("Invalid\n");
    }
    return EXIT_SUCCESS;
}