#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

long long sum_of_squares_of_odd_numbers(int n) {
    if (n <= 0) {
        return 0;
    }
    
    if (n > INT_MAX / 2) {
        return -1;
    }
    
    long long term1 = n;
    long long term2 = 2LL * n - 1;
    long long term3 = 2LL * n + 1;
    
    if (term2 > LLONG_MAX / term1) {
        return -1;
    }
    long long product = term1 * term2;
    
    if (term3 > LLONG_MAX / product) {
        return -1;
    }
    product *= term3;
    
    return product / 3;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[64];
    char *endptr;
    long val;
    
    printf("Enter a positive integer n: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    val = strtol(input, &endptr, 10);
    
    if (endptr == input || (*endptr != '\n' && *endptr != '\0')) {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return EXIT_FAILURE;
    }
    
    /* Possible weaknesses found:
     *  Assuming that condition 'val<=0' is not redundant
     */
    if (errno == ERANGE || val <= 0 || val > INT_MAX) {
        fprintf(stderr, "n must be a positive integer within valid range.\n");
        return EXIT_FAILURE;
    }
    
    /* Possible weaknesses found:
     *  Assignment 'n=(int)val', assigned value is greater than 0
     */
    int n = (int)val;
    long long result = sum_of_squares_of_odd_numbers(n);
    
    /* Possible weaknesses found:
     *  Condition 'n>0' is always true
     *  Condition 'n>0' is always true [knownConditionTrueFalse]
     */
    if (result == -1 && n > 0) {
        fprintf(stderr, "Integer overflow detected. Please use a smaller value.\n");
        return EXIT_FAILURE;
    }
    
    printf("Sum of squares of first %d odd natural numbers: %lld\n", 
           n, result);
    
    return EXIT_SUCCESS;
}