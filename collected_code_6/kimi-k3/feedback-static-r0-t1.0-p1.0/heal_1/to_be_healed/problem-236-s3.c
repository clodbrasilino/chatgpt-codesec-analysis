#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int count_max_equilateral_triangles(int side_length) {
    if (side_length <= 0) {
        return 0;
    }
    
    if (side_length > INT_MAX / side_length) {
        return -1;
    }
    
    int total = 0;
    int size;
    
    /* Possible weaknesses found:
     *  Assuming that condition 'size<=side_length' is not redundant
     */
    for (size = 1; size <= side_length; size++) {
        /* Possible weaknesses found:
         *  Assignment 'count=side_length-size+1', assigned value is greater than 0
         */
        int count = side_length - size + 1;
        /* Possible weaknesses found:
         *  Condition 'count>0' is always true
         *  Condition 'count>0' is always true [knownConditionTrueFalse]
         */
        if (count > 0) {
            if (total > INT_MAX - count) {
                return -1;
            }
            total += count;
        }
    }
    
    return total;
}

int main(void) {
    int side_length;
    int result;
    
    printf("Enter the side length of the equilateral triangle: ");
    
    if (scanf("%d", &side_length) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (side_length < 0) {
        fprintf(stderr, "Side length must be non-negative\n");
        return EXIT_FAILURE;
    }
    
    result = count_max_equilateral_triangles(side_length);
    
    if (result < 0) {
        fprintf(stderr, "Overflow occurred during calculation\n");
        return EXIT_FAILURE;
    }
    
    printf("Maximum number of equilateral triangles: %d\n", result);
    
    return EXIT_SUCCESS;
}