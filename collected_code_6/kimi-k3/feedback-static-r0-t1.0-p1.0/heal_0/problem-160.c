#include <stdio.h>
#include <stdlib.h>

long long extended_gcd(long long a, long long b, long long *x, long long *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    long long x1, y1;
    long long gcd = extended_gcd(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;
    return gcd;
}

int find_solution(long long a, long long b, long long n, long long *x, long long *y) {
    if (x == NULL || y == NULL) {
        return 0;
    }
    if (a == 0 && b == 0) {
        return (n == 0) ? 1 : 0;
    }
    long long gcd = extended_gcd(a, b, x, y);
    if (n % gcd != 0) {
        return 0;
    }
    *x *= n / gcd;
    *y *= n / gcd;
    return 1;
}

int main(void) {
    long long a, b, n, x, y;
    
    if (scanf("%lld %lld %lld", &a, &b, &n) != 3) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (find_solution(a, b, n, &x, &y)) {
        printf("%lld %lld\n", x, y);
    } else {
        printf("No solution exists\n");
    }
    
    return EXIT_SUCCESS;
}