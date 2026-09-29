#include <stdio.h>

void find_xy(int a, int b, int n, int *x, int *y) {
    for(*x = 0; *x <= n; (*x)++) {
        for(*y = 0; *y <= n; (*y)++) {
            if((a * (*x) + b * (*y)) == n) {
                return;
            }
        }
    }
}

int main() {
    int a = 3, b = 2, n = 7;
    int x, y;
    find_xy(a, b, n, &x, &y);
    printf("x = %d, y = %d\n", x, y);
    return 0;
}