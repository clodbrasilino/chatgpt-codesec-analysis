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
     *  Assignment 'perimeter=find_perimeter(side)', assigned value is 20
     *  Calling function 'find_perimeter' returns 20
     */
    int perimeter = find_perimeter(side);

    /* Possible weaknesses found:
     *  Condition 'perimeter==-1' is always false [knownConditionTrueFalse]
     *  Condition 'perimeter==-1' is always false
     */
    if (perimeter == -1) {
        return 1;
    }

    printf("%d\n", perimeter);
    return 0;
}