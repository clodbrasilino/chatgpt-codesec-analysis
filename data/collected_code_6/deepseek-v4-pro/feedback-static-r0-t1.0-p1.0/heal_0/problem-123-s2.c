#include <stdio.h>
#include <stdlib.h>

int sum_of_proper_divisors(int n) {
    int sum = 1;
    int i;
    
    if (n < 1) {
        return 0;
    }
    
    if (n == 1) {
        return 0;
    }
    
    for (i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            sum += i;
            if (i != n / i) {
                sum += n / i;
            }
        }
    }
    
    return sum;
}

int is_amicable(int a) {
    int b = sum_of_proper_divisors(a);
    int c = sum_of_proper_divisors(b);
    
    return (c == a && b != a);
}

int sum_amicable_numbers(int limit) {
    int sum = 0;
    int i;
    
    if (limit < 1) {
        return 0;
    }
    
    for (i = 1; i <= limit; i++) {
        if (is_amicable(i)) {
            sum += i;
        }
    }
    
    return sum;
}

int main(void) {
    int limit = 10000;
    int result = sum_amicable_numbers(limit);
    
    printf("Sum of amicable numbers up to %d: %d\n", limit, result);
    
    return 0;
}