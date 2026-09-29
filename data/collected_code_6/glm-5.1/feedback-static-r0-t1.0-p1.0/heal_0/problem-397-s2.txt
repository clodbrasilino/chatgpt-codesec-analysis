#include <stdio.h>

int median_of_three(int a, int b, int c) {
    if ((a > b) != (a > c)) {
        return a;
    }
    if ((b > a) != (b > c)) {
        return b;
    }
    return c;
}

int main(void) {
    int x, y, z;
    if (scanf("%d %d %d", &x, &y, &z) == 3) {
        printf("%d\n", median_of_three(x, y, z));
        return 0;
    }
    return 1;
}