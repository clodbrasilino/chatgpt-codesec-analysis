#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long arithmetic_progression_nth_term(long long first_term, long long common_difference, unsigned long long n) {
    if (n == 0) {
        return 0;
    }
    
    if (common_difference == 0) {
        return first_term;
    }
    
    if (n == 1) {
        return first_term;
    }
    
    if (n - 1 > LLONG_MAX) {
        return 0;
    }
    
    if (common_difference > 0) {
        if (first_term > LLONG_MAX - (long long)(n - 1) * common_difference) {
            return 0;
        }
    } else if (common_difference < 0) {
        if (first_term < LLONG_MIN - (long long)(n - 1) * common_difference) {
            return 0;
        }
    }
    
    if ((long long)(n - 1) > LLONG_MAX / common_difference && common_difference != 0) {
        return 0;
    }
    
    if ((long long)(n - 1) < LLONG_MIN / common_difference && common_difference != 0) {
        return 0;
    }
    
    return first_term + (long long)(n - 1) * common_difference;
}

int main(void) {
    long long first_term = 0;
    long long common_difference = 0;
    unsigned long long n = 0;
    long long result = 0;
    
    printf("Enter first term: ");
    if (scanf("%lld", &first_term) != 1) {
        printf("Invalid input\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter common difference: ");
    if (scanf("%lld", &common_difference) != 1) {
        printf("Invalid input\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter term position (n): ");
    if (scanf("%llu", &n) != 1) {
        printf("Invalid input\n");
        return EXIT_FAILURE;
    }
    
    result = arithmetic_progression_nth_term(first_term, common_difference, n);
    
    printf("The %llu-th term is: %lld\n", n, result);
    
    return EXIT_SUCCESS;
}