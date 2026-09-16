#include <stdio.h>
#include <stdlib.h>

long long sum_common_divisors(long long a, long long b) {
    if (a == 0 && b == 0) {
        return 0;
    }
    
    if (a < 0) {
        a = -a;
    }
    if (b < 0) {
        b = -b;
    }
    
    long long gcd_val = a;
    long long temp = b;
    
    while (temp != 0) {
        long long remainder = gcd_val % temp;
        gcd_val = temp;
        temp = remainder;
    }
    
    long long sum = 0;
    for (long long i = 1; i <= gcd_val / i; i++) {
        if (gcd_val % i == 0) {
            sum += i;
            if (i != gcd_val / i) {
                sum += gcd_val / i;
            }
        }
    }
    
    return sum;
}

int main(void) {
    long long num1, num2;
    
    if (scanf("%lld %lld", &num1, &num2) != 2) {
        return EXIT_FAILURE;
    }
    
    long long result = sum_common_divisors(num1, num2);
    printf("%lld\n", result);
    
    return EXIT_SUCCESS;
}