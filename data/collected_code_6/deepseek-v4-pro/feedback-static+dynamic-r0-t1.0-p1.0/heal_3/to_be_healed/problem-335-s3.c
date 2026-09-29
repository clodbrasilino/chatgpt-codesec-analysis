#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int sum_arithmetic_progression(int first_term, int common_difference, int number_of_terms) {
    if (number_of_terms <= 0) {
        return 0;
    }
    
    if (common_difference == 0) {
        long long product = (long long)first_term * number_of_terms;
        if (product > INT_MAX || product < INT_MIN) {
            return 0;
        }
        return (int)product;
    }
    
    long long ll_first = first_term;
    long long ll_diff = common_difference;
    long long ll_n = number_of_terms;
    
    long long last_term = ll_first + (ll_n - 1) * ll_diff;
    
    long long sum_first_last = ll_first + last_term;
    
    long long sum;
    if (ll_n % 2 == 0) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 222222222 * 1975308438024700 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000009,time:13225,execs:8549,op:havoc,rep:4)
         */
        sum = (ll_n / 2) * sum_first_last;
    } else {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 1494771481 * 3321382228564 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000009,time:13007,execs:8411,op:havoc,rep:2)
         */
        sum = ll_n * (sum_first_last / 2);
    }
    
    if (sum > INT_MAX || sum < INT_MIN) {
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