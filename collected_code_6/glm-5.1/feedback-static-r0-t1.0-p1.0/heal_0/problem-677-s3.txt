#include <stdio.h>

int is_triangle_valid(int a, int b, int c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        return 0;
    }
    if ((long)a + (long)b > c && (long)b + (long)c > a && (long)a + (long)c > b) {
        return 1;
    }
    return 0;
}

int main(void) {
    int a, b, c;
    if (scanf("%d %d %d", &a, &b, &c) != 3) {
        return 1;
    }
    if (is_triangle_valid(a, b, c)) {
        printf("Valid\n");
    } else {
        printf("Invalid\n");
    }
    return 0;
}