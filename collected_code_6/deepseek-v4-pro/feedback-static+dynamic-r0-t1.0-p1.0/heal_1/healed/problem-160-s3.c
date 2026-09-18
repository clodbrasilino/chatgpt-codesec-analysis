#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

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

int mul_overflow(int a, int b, int *result) {
    if (a == 0 || b == 0) {
        *result = 0;
        return 0;
    }
    int64_t res = (int64_t)a * (int64_t)b;
    if (res > INT_MAX || res < INT_MIN) {
        return 1;
    }
    *result = (int)res;
    return 0;
}

int add_overflow(int a, int b, int *result) {
    int64_t res = (int64_t)a + (int64_t)b;
    if (res > INT_MAX || res < INT_MIN) {
        return 1;
    }
    *result = (int)res;
    return 0;
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
    int gcd = extended_gcd(abs(a), abs(b), &x0, &y0);
    
    if (n % gcd != 0) {
        return 0;
    }
    
    int factor = n / gcd;
    int scaled_x0, scaled_y0;
    
    if (mul_overflow(x0, factor, &scaled_x0)) {
        return 0;
    }
    if (mul_overflow(y0, factor, &scaled_y0)) {
        return 0;
    }
    
    x0 = scaled_x0;
    y0 = scaled_y0;
    
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    
    *x = x0;
    *y = y0;
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
        int term1, term2, sum;
        if (mul_overflow(a, x, &term1) || mul_overflow(b, y, &term2) || add_overflow(term1, term2, &sum)) {
            printf("Verification: overflow in calculation\n");
        } else {
            printf("Verification: %d*%d + %d*%d = %d\n", a, x, b, y, sum);
        }
    } else {
        printf("No integer solution exists\n");
    }
    
    return EXIT_SUCCESS;
}