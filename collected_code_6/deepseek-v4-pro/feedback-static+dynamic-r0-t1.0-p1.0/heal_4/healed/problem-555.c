#include <stdio.h>
#include <limits.h>

long long difference(long long n) {
    long long sum_n;
    long long sum_cubes;
    
    if (n < 1) {
        return -1;
    }
    
    if (n % 2 == 0) {
        if (n > LLONG_MAX / (n + 1) * 2) {
            return -1;
        }
        if (n + 1 > LLONG_MAX / (n / 2)) {
            return -1;
        }
        sum_n = n / 2;
        if (sum_n > LLONG_MAX / (n + 1)) {
            return -1;
        }
        sum_n = sum_n * (n + 1);
    } else {
        if (n == LLONG_MAX) {
            return -1;
        }
        if (n > LLONG_MAX / ((n + 1) / 2)) {
            return -1;
        }
        sum_n = (n + 1) / 2;
        if (sum_n > LLONG_MAX / n) {
            return -1;
        }
        sum_n = sum_n * n;
    }
    
    if (sum_n > 3037000499LL) {
        return -1;
    }
    
    if (sum_n > LLONG_MAX / sum_n) {
        return -1;
    }
    sum_cubes = sum_n * sum_n;
    
    if (sum_cubes > LLONG_MAX - sum_n) {
        return -1;
    }
    
    return sum_cubes - sum_n;
}

int main(void) {
    long long n;
    
    printf("Enter a natural number: ");
    if (scanf("%lld", &n) != 1 || n < 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    long long result = difference(n);
    if (result == -1) {
        printf("Overflow occurred\n");
        return 1;
    }
    
    printf("Difference: %lld\n", result);
    
    return 0;
}