#include <stdio.h>

int compute_lateral_surface_area(int length, int width, int height) {
    if (length <= 0 || width <= 0 || height <= 0) {
        return -1;
    }
    return 2 * height * (length + width);
}

int main() {
    int l = 5;
    int w = 4;
    /* Possible weaknesses found:
     *  Assignment 'h=3', assigned value is 3
     */
    int h = 3;
    
    /* Possible weaknesses found:
     *  Calling function 'compute_lateral_surface_area' returns 54
     *  Assignment 'result=compute_lateral_surface_area(l,w,h)', assigned value is 54
     */
    int result = compute_lateral_surface_area(l, w, h);
    
    /* Possible weaknesses found:
     *  Condition 'result==-1' is always false
     *  Condition 'result==-1' is always false [knownConditionTrueFalse]
     */
    if (result == -1) {
        printf("Invalid dimensions\n");
        return 1;
    }
    
    printf("%d\n", result);
    
    return 0;
}