#include <stdio.h>
#include <stdlib.h>

int gcd_extended(int a, int b, int *x, int *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    
    int x1, y1;
    int gcd = gcd_extended(b, a % b, &x1, &y1);
    
    *x = y1;
    *y = x1 - (a / b) * y1;
    
    return gcd;
}

int find_solution(int a, int b, int n, int *x, int *y) {
    if (a == 0 && b == 0) {
        if (n == 0) {
            *x = 0;
            *y = 0;
            return 1;
        }
        return 0;
    }

    int x0, y0;
    int g = gcd_extended(abs(a), abs(b), &x0, &y0);

    if (n % g != 0) {
        return 0;
    }

    *x = x0 * (n / g);
    *y = y0 * (n / g);

    if (a < 0) {
        *x = -*x;
    }
    if (b < 0) {
        *y = -*y;
    }

    return 1;
}

int main(void) {
    int a = 4;
    int b = 6;
    int n = 10;
    int x, y;

    if (find_solution(a, b, n, &x, &y)) {
        printf("%d * %d + %d * %d = %d\n", a, x, b, y, n);
    } else {
        printf("No solution\n");
    }

    return 0;
}