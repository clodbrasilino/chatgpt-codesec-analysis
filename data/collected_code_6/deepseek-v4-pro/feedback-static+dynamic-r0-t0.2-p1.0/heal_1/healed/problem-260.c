#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

bool is_prime(long long n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (long long i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

long long nsw_prime(int n) {
    if (n <= 0) return -1;
    
    long long a = 1;
    long long b = 1;
    int count = 0;
    long long result = -1;
    
    if (is_prime(a)) {
        count++;
        if (count == n) return a;
    }
    
    if (count < n && is_prime(b)) {
        count++;
        if (count == n) return b;
    }
    
    while (count < n) {
        long long c = 2 * b + a;
        if (c < 0) return -1;
        
        if (is_prime(c)) {
            count++;
            if (count == n) {
                result = c;
                break;
            }
        }
        
        a = b;
        b = c;
    }
    
    return result;
}

int main(void) {
    int n;
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    long long result = nsw_prime(n);
    if (result == -1) {
        printf("Could not find the %dth NSW prime\n", n);
        return 1;
    }
    
    printf("The %dth NSW prime is: %lld\n", n, result);
    return 0;
}