#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int extended_gcd(int a, int b, long long *x, long long *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    long long x1, y1;
    int gcd = extended_gcd(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;
    return gcd;
}

int find_solution(int a, int b, int n, long long *x, long long *y) {
    if (a == 0 && b == 0) {
        return n == 0 ? 1 : 0;
    }
    
    long long x0, y0;
    int gcd = extended_gcd(a < 0 ? -a : a, b < 0 ? -b : b, &x0, &y0);
    
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    
    if (n % gcd != 0) {
        return 0;
    }
    
    long long scale = (long long)n / gcd;
    long long result_x = x0 * scale;
    long long result_y = y0 * scale;
    
    if (result_x > INT_MAX || result_x < INT_MIN || result_y > INT_MAX || result_y < INT_MIN) {
        return 0;
    }
    
    *x = result_x;
    *y = result_y;
    
    return 1;
}

int main(void) {
    int a, b, n;
    long long x, y;
    
    printf("Enter a, b, n: ");
    if (scanf("%d %d %d", &a, &b, &n) != 3) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (find_solution(a, b, n, &x, &y)) {
        printf("Solution: x = %lld, y = %lld\n", x, y);
        long long verification = (long long)a * x + (long long)b * y;
        printf("Verification: %d*%lld + %d*%lld = %lld\n", a, x, b, y, verification);
    } else {
        printf("No solution exists\n");
    }
    
    return EXIT_SUCCESS;
}