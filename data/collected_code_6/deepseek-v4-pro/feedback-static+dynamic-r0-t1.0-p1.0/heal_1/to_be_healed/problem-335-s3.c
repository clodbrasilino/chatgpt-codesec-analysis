#include <stdio.h>
#include <stdlib.h>

int sum_arithmetic_progression(int first_term, int common_difference, int number_of_terms) {
    if (number_of_terms <= 0) {
        return 0;
    }
    
    if (common_difference == 0) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 307163591 * 12 cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000008,time:11240,execs:4930,op:havoc,rep:3)
         */
        return first_term * number_of_terms;
    }
    
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 1111111110 * 4 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000006,time:2412,execs:1084,op:havoc,rep:10)
     */
    int last_term = first_term + (number_of_terms - 1) * common_difference;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 1111111111 + 1111111771 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000006,time:4922,execs:2210,op:havoc,rep:13)
     */
    long long sum = (long long)number_of_terms * (first_term + last_term) / 2;
    
    if (sum > 2147483647LL || sum < -2147483648LL) {
        return 0;
    }
    
    return (int)sum;
}

int main(void) {
    int a1, d, n;
    int result;
    
    printf("Enter first term: ");
    if (scanf("%d", &a1) != 1) {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter common difference: ");
    if (scanf("%d", &d) != 1) {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter number of terms: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n <= 0) {
        fprintf(stderr, "Error: Number of terms must be positive\n");
        return EXIT_FAILURE;
    }
    
    result = sum_arithmetic_progression(a1, d, n);
    printf("Sum of arithmetic progression: %d\n", result);
    
    return EXIT_SUCCESS;
}