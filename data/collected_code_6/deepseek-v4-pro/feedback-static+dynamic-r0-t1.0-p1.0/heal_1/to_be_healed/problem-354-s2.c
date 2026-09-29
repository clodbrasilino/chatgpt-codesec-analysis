#include <stdio.h>
#include <stdlib.h>

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
    
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 1 + 9223372036854775807 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:4175,execs:1850,op:havoc,rep:2)
     * UBSan: signed integer overflow: 554 * 9223372036854775807 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:4077,execs:1809,op:havoc,rep:2)
     */
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