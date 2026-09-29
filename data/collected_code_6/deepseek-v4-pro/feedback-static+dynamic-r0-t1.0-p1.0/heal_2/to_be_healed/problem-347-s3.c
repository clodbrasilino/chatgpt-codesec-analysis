#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

long long count_squares(int length, int width) {
    /* Possible weaknesses found:
     *  Assuming that condition 'width<=0' is not redundant
     *  Assuming that condition 'length<=0' is not redundant
     */
    if (length <= 0 || width <= 0) {
        return 0;
    }
    
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (length > 1000000 || width > 1000000) {
        return -1;
    }
    
    long long total = 0;
    /* Possible weaknesses found:
     *  ll_length is assigned 'length' here.
     */
    long long ll_length = length;
    /* Possible weaknesses found:
     *  ll_width is assigned 'width' here.
     */
    long long ll_width = width;
    long long min_dim = ll_length < ll_width ? ll_length : ll_width;
    
    for (long long size = 1; size <= min_dim; size++) {
        /* Possible weaknesses found:
         *  Assignment 'term1=ll_length-size+1', assigned value is greater than 0
         */
        long long term1 = ll_length - size + 1;
        /* Possible weaknesses found:
         *  Assignment 'term2=ll_width-size+1', assigned value is greater than 0
         */
        long long term2 = ll_width - size + 1;
        
        /* Possible weaknesses found:
         *  Condition 'term1>0' is always true
         *  Condition 'term2>0' is always true
         *  Condition 'term1>0' is always true [knownConditionTrueFalse]
         *  Condition 'term2>0' is always true [knownConditionTrueFalse]
         */
        if (term1 > 0 && term2 > 0) {
            if (term2 > LLONG_MAX / term1) {
                return -1;
            }
            total += term1 * term2;
        }
    }
    
    return total;
}

int main(void) {
    long long length, width;
    
    printf("Enter length and width of rectangle: ");
    if (scanf("%lld %lld", &length, &width) != 2) {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (length <= 0 || width <= 0) {
        fprintf(stderr, "Error: Dimensions must be positive\n");
        return EXIT_FAILURE;
    }
    
    if (length > INT_MAX || width > INT_MAX) {
        fprintf(stderr, "Error: Dimensions too large\n");
        return EXIT_FAILURE;
    }
    
    long long result = count_squares((int)length, (int)width);
    
    if (result < 0) {
        fprintf(stderr, "Error: Result overflow or dimensions too large\n");
        return EXIT_FAILURE;
    }
    
    printf("Number of squares: %lld\n", result);
    
    return EXIT_SUCCESS;
}