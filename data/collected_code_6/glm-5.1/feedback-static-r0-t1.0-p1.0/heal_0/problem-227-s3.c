#include <stdio.h>

int min_of_three(int a, int b, int c) {
    int min = a;
    if (b < min) {
        min = b;
    }
    if (c < min) {
        min = c;
    }
    return min;
}

int main(void) {
    int x, y, z;
    if (scanf("%d %d %d", &x, &y, &z) == 3) {
        printf("%d\n", min_of_three(x, y, z));
        return 0;
    }
    return 1;
}