#include <stdio.h>

int lateral_surface_area(int side) {
    if (side < 0) {
        return -1;
    }
    return 4 * side * side;
}

int main() {
    /* Possible weaknesses found:
     *  Assignment 'side=5', assigned value is 5
     */
    int side = 5;
    /* Possible weaknesses found:
     *  Calling function 'lateral_surface_area' returns 100
     *  Assignment 'area=lateral_surface_area(side)', assigned value is 100
     */
    int area = lateral_surface_area(side);
    /* Possible weaknesses found:
     *  Condition 'area==-1' is always false [knownConditionTrueFalse]
     *  Condition 'area==-1' is always false
     */
    if (area == -1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    printf("%d\n", area);
    return 0;
}