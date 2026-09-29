#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long sum_of_divisors(long long n) {
    if (n <= 0) {
        return -1;
    }
    
    long long sum = 0;
    long long i;
    
    for (i = 1; i <= n / i; i++) {
        if (n % i == 0) {
            sum += i;
            if (i != n / i) {
                sum += n / i;
            }
        }
    }
    
    return sum;
}

int check_same_sum_of_divisors(long long a, long long b) {
    if (a <= 0 || b <= 0) {
        return -1;
    }
    
    long long sum_a = sum_of_divisors(a);
    long long sum_b = sum_of_divisors(b);
    
    if (sum_a == -1 || sum_b == -1) {
        return -1;
    }
    
    return (sum_a == sum_b) ? 1 : 0;
}

int main(void) {
    long long num1, num2;
    int result;
    
    printf("Enter first positive integer: ");
    if (scanf("%lld", &num1) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter second positive integer: ");
    if (scanf("%lld", &num2) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    result = check_same_sum_of_divisors(num1, num2);
    
    if (result == -1) {
        fprintf(stderr, "Error: Numbers must be positive integers\n");
        return EXIT_FAILURE;
    } else if (result == 1) {
        printf("The sum of divisors is the same.\n");
    } else {
        printf("The sum of divisors is different.\n");
    }
    
    return EXIT_SUCCESS;
}