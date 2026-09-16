#include <stdio.h>

int find_perimeter(int side) {
    if (side < 0) {
        return -1;
    }
    return side * 4;
}

int main() {
    /* Possible weaknesses found:
     *  Assignment 'side=5', assigned value is 5
     */
    int side = 5;
    
    /* Possible weaknesses found:
     *  Condition 'side<0' is always false [knownConditionTrueFalse]
     *  Condition 'side<0' is always false
     */
    if (side < 0) {
        return 1;
    }

    int perimeter = find_perimeter(side);

    printf("%d\n", perimeter);
    return 0;
}