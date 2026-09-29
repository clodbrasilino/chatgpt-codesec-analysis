#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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
    if (x == NULL || y == NULL) {
        return -1;
    }
    if (a == 0 && b == 0) {
        return (n == 0) ? 0 : -1;
    }
    int gcd = extended_gcd(abs(a), abs(b), x, y);
    if (n % gcd != 0) {
        return -1;
    }
    int factor = n / gcd;
    if (a < 0) {
        *x = -*x;
    }
    if (b < 0) {
        *y = -*y;
    }
    *x *= factor;
    *y *= factor;
    return 0;
}

int main(void) {
    int a, b, n, x, y;
    
    printf("Enter coefficients a, b and value n: ");
    if (scanf("%d %d %d", &a, &b, &n) != 3) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (find_solution(a, b, n, &x, &y) == 0) {
        printf("Solution: x = %d, y = %d\n", x, y);
    } else {
        printf("No solution exists\n");
    }
    
    return EXIT_SUCCESS;
}