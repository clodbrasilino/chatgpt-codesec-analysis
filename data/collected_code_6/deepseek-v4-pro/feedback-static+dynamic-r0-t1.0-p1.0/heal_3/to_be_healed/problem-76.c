#include <stdio.h>
#include <limits.h>

long long count_squares(int length, int width) {
    if (length <= 0 || width <= 0) {
        return 0;
    }
    
    long long total = 0;
    int min = length < width ? length : width;
    int max = length > width ? length : width;
    
    /* Possible weaknesses found:
     *  Assuming that condition 'k<min' is not redundant
     */
    for (int k = 0; k < min; k++) {
        /* Possible weaknesses found:
         *  Assignment 'term1=(long long)(min-k)', assigned value is greater than 0
         */
        long long term1 = (long long)(min - k);
        long long term2 = (long long)(max - k);
        
        /* Possible weaknesses found:
         *  Condition 'term1>0' is always true
         *  Condition 'term1>0' is always true [knownConditionTrueFalse]
         */
        if (term1 > 0 && term2 > 0 && term1 > LLONG_MAX / term2) {
            return -1;
        }
        
        long long product = term1 * term2;
        
        if (product > 0 && total > LLONG_MAX - product) {
            return -1;
        }
        
        total += product;
    }
    
    return total;
}

int main(void) {
    int length, width;
    
    printf("Enter length and width of rectangle: ");
    if (scanf("%d %d", &length, &width) != 2) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    long long result = count_squares(length, width);
    if (result == -1) {
        fprintf(stderr, "Overflow detected\n");
        return 1;
    }
    
    printf("Number of squares: %lld\n", result);
    
    return 0;
}