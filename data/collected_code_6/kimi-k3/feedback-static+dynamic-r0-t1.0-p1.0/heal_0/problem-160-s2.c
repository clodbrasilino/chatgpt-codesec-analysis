#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

typedef struct {
    long long x;
    long long y;
    long long gcd;
} ExtendedGcdResult;

static long long safe_abs(long long val, bool *error) {
    if (val == LLONG_MIN) {
        *error = true;
        return 0;
    }
    return (val < 0) ? -val : val;
}

static ExtendedGcdResult extended_gcd(long long a, long long b, bool *error) {
    ExtendedGcdResult result = {0, 0, 0};
    long long old_r = a, r = b;
    long long old_s = 1, s = 0;
    long long old_t = 0, t = 1;
    
    while (r != 0) {
        if (old_r == LLONG_MIN || r == LLONG_MIN) {
            *error = true;
            return result;
        }
        
        long long quotient = old_r / r;
        
        long long temp_r = r;
        long long temp_s = s;
        long long temp_t = t;
        
        if ((quotient > 0 && r > LLONG_MAX / quotient) ||
            (quotient > 0 && r < LLONG_MIN / quotient) ||
            (quotient < 0 && r > LLONG_MIN / quotient) ||
            (quotient < 0 && r < LLONG_MAX / quotient)) {
            *error = true;
            return result;
        }
        
        r = old_r - quotient * r;
        
        if ((quotient > 0 && s > LLONG_MAX / quotient) ||
            (quotient > 0 && s < LLONG_MIN / quotient) ||
            (quotient < 0 && s > LLONG_MIN / quotient) ||
            (quotient < 0 && s < LLONG_MAX / quotient)) {
            *error = true;
            return result;
        }
        
        s = old_s - quotient * s;
        
        if ((quotient > 0 && t > LLONG_MAX / quotient) ||
            (quotient > 0 && t < LLONG_MIN / quotient) ||
            (quotient < 0 && t > LLONG_MIN / quotient) ||
            (quotient < 0 && t < LLONG_MAX / quotient)) {
            *error = true;
            return result;
        }
        
        t = old_t - quotient * t;
        
        old_r = temp_r;
        old_s = temp_s;
        old_t = temp_t;
    }
    
    result.x = old_s;
    result.y = old_t;
    result.gcd = old_r;
    
    if (result.gcd < 0) {
        if (result.gcd == LLONG_MIN) {
            *error = true;
            return result;
        }
        result.gcd = -result.gcd;
        if (result.x != LLONG_MIN) result.x = -result.x;
        if (result.y != LLONG_MIN) result.y = -result.y;
    }
    
    return result;
}

int solve_linear_diophantine(long long a, long long b, long long n, 
                             long long *x_out, long long *y_out) {
    if (x_out == NULL || y_out == NULL) {
        return -1;
    }
    
    if (a == 0 && b == 0) {
        if (n == 0) {
            *x_out = 0;
            *y_out = 0;
            return 0;
        }
        return -1;
    }
    
    bool error = false;
    ExtendedGcdResult eg = extended_gcd(a, b, &error);
    
    if (error || eg.gcd == 0) {
        return -1;
    }
    
    if (n % eg.gcd != 0) {
        return -1;
    }
    
    long long factor = n / eg.gcd;
    
    if ((factor > 0 && eg.x > LLONG_MAX / factor) ||
        (factor > 0 && eg.x < LLONG_MIN / factor) ||
        (factor < 0 && eg.x > LLONG_MIN / factor) ||
        (factor < 0 && eg.x < LLONG_MAX / factor) ||
        (factor > 0 && eg.y > LLONG_MAX / factor) ||
        (factor > 0 && eg.y < LLONG_MIN / factor) ||
        (factor < 0 && eg.y > LLONG_MIN / factor) ||
        (factor < 0 && eg.y < LLONG_MAX / factor)) {
        return -1;
    }
    
    *x_out = eg.x * factor;
    *y_out = eg.y * factor;
    
    return 0;
}

int main(void) {
    long long a, b, n;
    long long x, y;
    
    printf("Enter coefficients a, b and constant n: ");
    
    if (scanf("%lld %lld %lld", &a, &b, &n) != 3) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (solve_linear_diophantine(a, b, n, &x, &y) == 0) {
        printf("Solution: x = %lld, y = %lld\n", x, y);
        printf("Verification: %lld * %lld + %lld * %lld = %lld\n", 
               a, x, b, y, a * x + b * y);
    } else {
        printf("No integer solution exists\n");
    }
    
    return EXIT_SUCCESS;
}