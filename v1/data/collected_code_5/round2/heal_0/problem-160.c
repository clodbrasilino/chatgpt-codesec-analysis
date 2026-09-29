#include <stdio.h>

void find_xy(int a, int b, int n, int* x, int* y) {
    if (a == 0 && b == 0) {
        printf("No solution exists\n");
        return;
    }
    if (a == 0) {
        *x = 0;
        *y = n / b;
    } else {
        *x = n / a;
        int remainder = n % a;
        *y = remainder / b;
    }
}

int main() {
    int a = 3, b = 2, n = 9;
    int x, y;
    find_xy(a, b, n, &x, &y);
    printf("x = %d, y = %d\n", x, y);
    return 0;
}