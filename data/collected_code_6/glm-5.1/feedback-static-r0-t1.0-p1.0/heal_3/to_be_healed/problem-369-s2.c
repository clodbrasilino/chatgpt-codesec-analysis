#include <stdio.h>

int compute_lateral_surface_area(int length, int width, int height) {
    if (length <= 0 || width <= 0 || height <= 0) {
        return -1;
    }
    return 2 * height * (length + width);
}

int main() {
    /* Possible weaknesses found:
     *  Assignment 'l=5', assigned value is 5
     */
    int l = 5;
    /* Possible weaknesses found:
     *  Assignment 'w=4', assigned value is 4
     */
    int w = 4;
    /* Possible weaknesses found:
     *  Assignment 'h=3', assigned value is 3
     */
    int h = 3;

    /* Possible weaknesses found:
     *  Condition 'l<=0' is always false [knownConditionTrueFalse]
     *  Condition 'h<=0' is always false [knownConditionTrueFalse]
     *  Condition 'l<=0' is always false
     *  Condition 'w<=0' is always false [knownConditionTrueFalse]
     *  Condition 'h<=0' is always false
     *  Condition 'w<=0' is always false
     */
    if (l <= 0 || w <= 0 || h <= 0) {
        printf("Invalid dimensions\n");
        return 1;
    }

    int result = compute_lateral_surface_area(l, w, h);
    
    printf("%d\n", result);
    
    return 0;
}