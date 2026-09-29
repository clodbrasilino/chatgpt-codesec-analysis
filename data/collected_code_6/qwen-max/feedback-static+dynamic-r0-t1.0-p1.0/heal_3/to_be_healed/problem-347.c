#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

size_t count_squares(int width, int height) {
    /* Possible weaknesses found:
     *  Assuming that condition 'width<=0' is not redundant
     *  Assuming that condition 'height<=0' is not redundant
     */
    if (width <= 0 || height <= 0) {
        return 0;
    }
    size_t count = 0;
    for (int side = 1; side <= (width < height ? width : height); ++side) {
        /* Possible weaknesses found:
         *  Assignment 'w=width-side+1', assigned value is greater than 0
         */
        int w = width - side + 1;
        /* Possible weaknesses found:
         *  Assignment 'h=height-side+1', assigned value is greater than 0
         */
        int h = height - side + 1;
        /* Possible weaknesses found:
         *  Condition 'w>0' is always true [knownConditionTrueFalse]
         *  Condition 'w>0' is always true
         *  Condition 'h>0' is always true [knownConditionTrueFalse]
         *  Condition 'h>0' is always true
         */
        if (w > 0 && h > 0 && (long long)w * h <= SIZE_MAX) {
            count += (size_t)w * (size_t)h;
        } else {
            break;
        }
    }
    return count;
}

int main() {
    int w, h;
    printf("Enter the width and height of the rectangle: ");
    if (scanf("%d %d", &w, &h) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    size_t result = count_squares(w, h);
    printf("Number of squares in the rectangle: %zu\n", result);
    return 0;
}