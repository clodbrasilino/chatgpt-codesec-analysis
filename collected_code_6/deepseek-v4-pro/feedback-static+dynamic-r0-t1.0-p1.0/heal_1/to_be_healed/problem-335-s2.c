#include <stdio.h>
#include <stdlib.h>

long long arithmetic_progression_sum(long long first_term, long long common_difference, long long number_of_terms) {
    if (number_of_terms <= 0) {
        return 0;
    }
    
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 4 * 9223372036854775807 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000003,time:3829,execs:1909,op:havoc,rep:1)
     * UBSan: signed integer overflow: 9223372036854775807 + 16 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000003,time:864,execs:452,op:havoc,rep:1)
     */
    long long last_term = first_term + (number_of_terms - 1) * common_difference;
    
    if (number_of_terms % 2 == 0) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 3333333 * 1333333332993333413 cannot be represented in type 'long long' (AFL crash: id:000003,sig:06,src:000004,time:19719,execs:9041,op:havoc,rep:21)
         */
        return (number_of_terms / 2) * (first_term + last_term);
    } else {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 11111111111111111 * 227888888888888871 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000003,time:3321,execs:1659,op:havoc,rep:3)
         */
        return number_of_terms * ((first_term + last_term) / 2);
    }
}

int main(void) {
    long long first_term, common_difference, number_of_terms;
    
    printf("Enter first term: ");
    if (scanf("%lld", &first_term) != 1) {
        fprintf(stderr, "Error: Invalid input for first term\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter common difference: ");
    if (scanf("%lld", &common_difference) != 1) {
        fprintf(stderr, "Error: Invalid input for common difference\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter number of terms: ");
    if (scanf("%lld", &number_of_terms) != 1) {
        fprintf(stderr, "Error: Invalid input for number of terms\n");
        return EXIT_FAILURE;
    }
    
    if (number_of_terms < 0) {
        fprintf(stderr, "Error: Number of terms cannot be negative\n");
        return EXIT_FAILURE;
    }
    
    long long sum = arithmetic_progression_sum(first_term, common_difference, number_of_terms);
    
    printf("Sum of arithmetic progression: %lld\n", sum);
    
    return EXIT_SUCCESS;
}