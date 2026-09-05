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
    int x = 0;
    int y = 0;
    int z = 0;

    if (scanf("%d %d %d", &x, &y, &z) != 3) {
        return 1;
    }

    printf("%d\n", count_equal(x, y, z));
    return 0;
}