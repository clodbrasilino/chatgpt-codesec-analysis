#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

long long sum_arithmetic_progression(long long first_term, long long common_difference, long long num_terms) {
    if (num_terms <= 0) {
        return 0;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 2 * 9223372036854775807 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:9419,execs:3756,op:havoc,rep:18)
     * UBSan: signed integer overflow: 56666666 * 377739988894 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000004,time:6419,execs:2523,op:havoc,rep:2)
     * UBSan: signed integer overflow: 2 * -9223372036854775807 cannot be represented in type 'long long' (AFL crash: id:000003,sig:06,src:000001,time:19163,execs:7648,op:havoc,rep:1)
     * UBSan: signed integer overflow: 2 + 9223372036854775807 cannot be represented in type 'long long' (AFL crash: id:000003,sig:06,src:000001,time:19163,execs:7648,op:havoc,rep:1)
     * UBSan: signed integer overflow: 4 * 9223372036854775807 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:8527,execs:3395,op:havoc,rep:4)
     */
    return (num_terms * (2 * first_term + (num_terms - 1) * common_difference)) / 2;
}

int main(void) {
    long long first_term, common_difference, num_terms;
    
    printf("Enter first term, common difference, and number of terms: ");
    
    if (scanf("%lld %lld %lld", &first_term, &common_difference, &num_terms) != 3) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (num_terms < 0) {
        fprintf(stderr, "Number of terms cannot be negative\n");
        return EXIT_FAILURE;
    }
    
    long long result = sum_arithmetic_progression(first_term, common_difference, num_terms);
    printf("Sum: %lld\n", result);
    
    return EXIT_SUCCESS;
}