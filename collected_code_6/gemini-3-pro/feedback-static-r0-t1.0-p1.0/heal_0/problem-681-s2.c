#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

long long find_smallest_prime_divisor(long long n) {
    if (n <= 1) {
        return -1; 
    }
    if (n % 2 == 0) {
        return 2;
    }
    if (n % 3 == 0) {
        return 3;
    }
    for (long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0) {
            return i;
        }
        if (n % (i + 2) == 0) {
            return i + 2;
        }
    }
    return n;
}

int main(void) {
    long long num = 0;
    
    if (scanf("%lld", &num) != 1) {
        return EXIT_FAILURE;
    }
    
    long long result = find_smallest_prime_divisor(num);
    
    if (result == -1) {
        printf("-1\n");
    } else {
        printf("%lld\n", result);
    }
    
    return EXIT_SUCCESS;
}