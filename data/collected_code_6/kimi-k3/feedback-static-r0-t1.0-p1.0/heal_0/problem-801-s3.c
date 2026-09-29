#include <stdio.h>

int count_equal(int a, int b, int c) {
    if (a == b && b == c) {
        return 3;
    } else if (a == b || b == c || a == c) {
        return 2;
    } else {
        return 0;
    }
}

int main(void) {
    int x, y, z;
    int result;

    if (scanf("%d %d %d", &x, &y, &z) != 3) {
        fprintf(stderr, "Error: invalid input\n");
        return 1;
    }

    result = count_equal(x, y, z);
    printf("%d\n", result);

    return 0;
}