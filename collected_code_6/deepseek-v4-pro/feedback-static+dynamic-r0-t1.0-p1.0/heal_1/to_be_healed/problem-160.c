#include <stdio.h>
#include <stdlib.h>

int extended_gcd(int a, int b, int *x, int *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    
    int x1, y1;
    int gcd = extended_gcd(b, a % b, &x1, &y1);
    
    *x = y1;
    *y = x1 - (a / b) * y1;
    
    return gcd;
}

int find_solution(int a, int b, int n, int *x, int *y) {
    if (a == 0 && b == 0) {
        return n == 0;
    }
    
    if (a == 0) {
        if (n % b == 0) {
            *x = 0;
            *y = n / b;
            return 1;
        }
        return 0;
    }
    
    if (b == 0) {
        if (n % a == 0) {
            *x = n / a;
            *y = 0;
            return 1;
        }
        return 0;
    }
    
    int x0, y0;
    int gcd = extended_gcd(a, b, &x0, &y0);
    
    if (n % gcd != 0) {
        return 0;
    }
    
    int multiplier = n / gcd;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -325794019 * 11 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:2684,execs:1338,op:havoc,rep:2)
     */
    *x = x0 * multiplier;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -14572895 * 44444 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000011,time:27679,execs:13080,op:havoc,rep:9)
     */
    *y = y0 * multiplier;
    
    return 1;
}

int main(void) {
    int a, b, n;
    int x, y;
    
    printf("Enter a, b, n: ");
    if (scanf("%d %d %d", &a, &b, &n) != 3) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (find_solution(a, b, n, &x, &y)) {
        printf("Solution: x = %d, y = %d\n", x, y);
        return EXIT_SUCCESS;
    } else {
        printf("No solution exists\n");
        return EXIT_FAILURE;
    }
}