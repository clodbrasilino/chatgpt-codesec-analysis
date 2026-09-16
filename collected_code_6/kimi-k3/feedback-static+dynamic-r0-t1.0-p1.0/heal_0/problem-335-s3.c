#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int sum_arithmetic_progression(int first_term, int common_diff, int num_terms, long *result)
{
    long long sum;
    
    if (result == NULL) {
        return -1;
    }
    
    if (num_terms < 0) {
        return -1;
    }
    
    if (num_terms == 0) {
        *result = 0;
        return 0;
    }
    
    sum = (long long)num_terms * (2LL * first_term + (long long)(num_terms - 1) * common_diff) / 2LL;
    
    if (sum > LONG_MAX || sum < LONG_MIN) {
        return -1;
    }
    
    *result = (long)sum;
    return 0;
}

int main(void)
{
    int first_term;
    int common_diff;
    int num_terms;
    long result;
    int scan_result;
    
    printf("Enter first term: ");
    scan_result = scanf("%d", &first_term);
    if (scan_result != 1) {
        fprintf(stderr, "Invalid input for first term\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter common difference: ");
    scan_result = scanf("%d", &common_diff);
    if (scan_result != 1) {
        fprintf(stderr, "Invalid input for common difference\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter number of terms: ");
    scan_result = scanf("%d", &num_terms);
    if (scan_result != 1) {
        fprintf(stderr, "Invalid input for number of terms\n");
        return EXIT_FAILURE;
    }
    
    if (sum_arithmetic_progression(first_term, common_diff, num_terms, &result) != 0) {
        fprintf(stderr, "Error: invalid parameters or result overflow\n");
        return EXIT_FAILURE;
    }
    
    printf("Sum of arithmetic progression: %ld\n", result);
    
    return EXIT_SUCCESS;
}