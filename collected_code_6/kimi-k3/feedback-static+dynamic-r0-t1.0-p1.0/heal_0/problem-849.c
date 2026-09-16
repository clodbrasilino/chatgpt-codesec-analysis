#include <stdio.h>
#include <stdlib.h>

long long sum_prime_divisors(long long n) {
    long long sum = 0;
    long long i;
    
    if (n < 0) {
        n = -n;
    }
    
    if (n == 0) {
        return 0;
    }
    
    if (n % 2 == 0) {
        sum += 2;
        while (n % 2 == 0) {
            n /= 2;
        }
    }
    
    for (i = 3; i <= n / i; i += 2) {
        if (n % i == 0) {
            sum += i;
            while (n % i == 0) {
                n /= i;
            }
        }
    }
    
    if (n > 1) {
        sum += n;
    }
    
    return sum;
}

int main(void) {
    long long num;
    long long result;
    
    if (scanf("%lld", &num) != 1) {
        return EXIT_FAILURE;
    }
    
    result = sum_prime_divisors(num);
    printf("%lld\n", result);
    
    return EXIT_SUCCESS;
}