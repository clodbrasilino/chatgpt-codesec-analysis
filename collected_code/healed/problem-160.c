#include <stdio.h>

void find_xy(int a, int b, int n, int *x, int *y) {
    *x = 1;
    int x1 = 0;
    *y = 0;
    int y1 = 1;
    int temp;
    
    while (b != 0) {
        int quotient = a / b;
        temp = b;
        b = a % b;
        a = temp;

        temp = x1;
        x1 = *x - quotient * x1;
        *x = temp;

        temp = y1;
        y1 = *y - quotient * y1;
        *y = temp;
    }
}

int main() {
    int a = 0, b = 0, n = 0, x = 0, y = 0;
    printf("Enter values for a, b and n: ");
    scanf("%d %d %d", &a, &b, &n);
    find_xy(a, b, n, &x, &y);
    printf("x = %d, y = %d\n", x, y);
    
    return 0;
}