#include <stdio.h>

int count_equal(int a, int b, int c) {
    if (a == b && b == c) {
        return 3;
    }
    if (a == b || b == c || a == c) {
        return 2;
    }
    return 0;
}

int main(void) {
    int a = 0;
    int b = 0;
    int c = 0;

    if (scanf("%d %d %d", &a, &b, &c) != 3) {
        return 1;
    }

    printf("%d\n", count_equal(a, b, c));
    return 0;
}