#include <stdio.h>
#include <stdlib.h>

long long sum_prime_divisors(long long n) {
    long long sum = 0;
    long long i;
    unsigned long long un;
    
    if (n < 0) {
        un = (unsigned long long)(-(n + 1)) + 1;
    } else {
        un = (unsigned long long)n;
    }
    
    if (un == 0) {
        return 0;
    }
    
    if (un % 2 == 0) {
        sum += 2;
        while (un % 2 == 0) {
            un /= 2;
        }
    }
    
    for (i = 3; (unsigned long long)i <= un / (unsigned long long)i; i += 2) {
        if (un % (unsigned long long)i == 0) {
            sum += i;
            while (un % (unsigned long long)i == 0) {
                un /= (unsigned long long)i;
            }
        }
    }
    
    if (un > 1) {
        sum += (long long)un;
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