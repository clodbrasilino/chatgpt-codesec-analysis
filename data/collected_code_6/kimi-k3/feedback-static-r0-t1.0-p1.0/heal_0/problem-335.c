#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

long long sum_arithmetic_progression(long long first_term, long long common_difference, long long num_terms) {
    if (num_terms <= 0) {
        return 0;
    }
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