#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

long long lcm(long long a, long long b) {
    long long g = gcd(a, b);
    if (a / g > LLONG_MAX / b) {
        return -1;
    }
    return (a / g) * b;
}

long long smallest_multiple(int n) {
    if (n <= 0) {
        return 0;
    }
    
    long long result = 1;
    for (int i = 2; i <= n; i++) {
        result = lcm(result, i);
        if (result == -1) {
            return -1;
        }
    }
    return result;
}

int main(void) {
    int n;
    
    if (scanf("%d", &n) != 1) {
        return 1;
    }
    
    if (n <= 0 || n > 100) {
        return 1;
    }
    
    long long result = smallest_multiple(n);
    if (result == -1) {
        return 1;
    }
    
    printf("%lld\n", result);
    
    return 0;
}