#include <stdio.h>
#include <stdlib.h>

int digit_sum(long long n) {
    int sum = 0;
    n = llabs(n);
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

void find_max_sum_parts(long long n, long long *a, long long *b) {
    if (n <= 0) {
        *a = 0;
        *b = 0;
        return;
    }
    
    long long power = 1;
    while (power <= n) {
        power *= 10;
    }
    power /= 10;

    if (power == 0) {
        *a = n;
        *b = 0;
        return;
    }

    *a = n;
    *b = 0;
    int max_sum = digit_sum(*a) + digit_sum(*b);

    long long current_a = n;
    long long current_b = 0;
    long long current_power = power;

    while (current_power > 0) {
        long long digit = (current_a / current_power) % 10;

        if (digit > 0) {
            current_a -= current_power;
            current_b += current_power;
            
            int current_sum = digit_sum(current_a) + digit_sum(current_b);
            if (current_sum > max_sum) {
                max_sum = current_sum;
                *a = current_a;
                *b = current_b;
            }
        }
        
        current_power /= 10;
    }
}

int main() {
    long long n = 54321;
    long long a, b;
    
    find_max_sum_parts(n, &a, &b);
    
    printf("%lld + %lld = %lld\n", a, b, a + b);
    printf("Sum of digits: %d\n", digit_sum(a) + digit_sum(b));
    
    return 0;
}