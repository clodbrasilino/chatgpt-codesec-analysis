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
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 211110 * 9223372036854775807 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:3122,execs:1637,op:havoc,rep:2)
         * UBSan: signed integer overflow: 9223372036854775807 - -211110 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:3122,execs:1637,op:havoc,rep:2)
         */
        if (first_term > LLONG_MAX - (long long)(n - 1) * common_difference) {
            return 0;
        }
    } else if (common_difference < 0) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 2555554 * -9223372036854775808 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000009,time:57456,execs:26618,op:havoc,rep:8)
         */
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