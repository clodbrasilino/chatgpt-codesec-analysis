#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int sum_common_divisors(int a, int b) {
    int g = gcd(abs(a), abs(b));
    long long sum = 0;
    int sqrt_g = (int)sqrt(g);
    
    for (int i = 1; i <= sqrt_g; i++) {
        if (g % i == 0) {
            if (sum > LLONG_MAX - i) {
                return INT_MAX;
            }
            sum += i;
            int other = g / i;
            if (other != i) {
                if (sum > LLONG_MAX - other) {
                    return INT_MAX;
                }
                sum += other;
            }
        }
    }
    
    if (sum > INT_MAX) {
        return INT_MAX;
    }
    
    return (int)sum;
}

int main(void) {
    int a, b;
    
    printf("Enter two integers: ");
    if (scanf("%d %d", &a, &b) != 2) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (a == 0 && b == 0) {
        fprintf(stderr, "Both numbers cannot be zero\n");
        return 1;
    }
    
    int result = sum_common_divisors(a, b);
    printf("Sum of common divisors: %d\n", result);
    
    return 0;
}