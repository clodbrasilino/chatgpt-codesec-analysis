#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long count_squares(int width, int height) {
    /* Possible weaknesses found:
     *  Assuming that condition 'width<=0' is not redundant
     */
    if (width <= 0 || height <= 0) {
        return 0;
    }
    
    /* Possible weaknesses found:
     *  w is assigned 'width' here.
     */
    long long w = width;
    long long h = height;
    long long total = 0;
    long long min_dim = (w < h) ? w : h;
    
    for (long long size = 1; size <= min_dim; size++) {
        /* Possible weaknesses found:
         *  Assignment 'a=w-size+1', assigned value is greater than 0
         */
        long long a = w - size + 1;
        long long b = h - size + 1;
        
        /* Possible weaknesses found:
         *  Condition 'a!=0' is always true
         *  Condition 'a!=0' is always true [knownConditionTrueFalse]
         */
        if (a != 0 && b > LLONG_MAX / a) {
            return -1;
        }
        
        long long term = a * b;
        
        if (total > LLONG_MAX - term) {
            return -1;
        }
        
        total += term;
    }
    
    return total;
}

int main(void) {
    int width, height;
    
    if (scanf("%d %d", &width, &height) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (width <= 0 || height <= 0) {
        fprintf(stderr, "Dimensions must be positive integers\n");
        return EXIT_FAILURE;
    }
    
    long long result = count_squares(width, height);
    
    if (result == -1) {
        fprintf(stderr, "Result too large\n");
        return EXIT_FAILURE;
    }
    
    printf("%lld\n", result);
    
    return EXIT_SUCCESS;
}