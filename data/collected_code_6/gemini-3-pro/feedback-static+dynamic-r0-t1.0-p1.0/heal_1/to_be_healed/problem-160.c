#include <stdio.h>
#include <stdlib.h>

int gcd_extended(int a, int b, int *x, int *y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }
    int x1, y1;
    int gcd = gcd_extended(b % a, a, &x1, &y1);
    *x = y1 - (b / a) * x1;
    *y = x1;
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
    if (a == 0) {
        if (n % b != 0) return 0;
        *x = 0;
        *y = n / b;
        return 1;
    }
    if (b == 0) {
        if (n % a != 0) return 0;
        *x = n / a;
        *y = 0;
        return 1;
    }

    int x_g, y_g;
    int g = gcd_extended(abs(a), abs(b), &x_g, &y_g);

    if (n % g != 0) {
        return 0;
    }

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -149589561 * 37222221 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000001,time:6099,execs:3123,op:havoc,rep:3)
     */
    *x = x_g * (n / g);
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -678894705 * 7 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:2352,execs:1208,op:havoc,rep:3)
     */
    *y = y_g * (n / g);

    if (a < 0) *x = -(*x);
    if (b < 0) *y = -(*y);

    return 1;
}

int main(void) {
    int a, b, n, x, y;

    if (scanf("%d %d %d", &a, &b, &n) != 3) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (find_solution(a, b, n, &x, &y)) {
        printf("%d %d\n", x, y);
    } else {
        printf("No solution\n");
    }

    return EXIT_SUCCESS;
}