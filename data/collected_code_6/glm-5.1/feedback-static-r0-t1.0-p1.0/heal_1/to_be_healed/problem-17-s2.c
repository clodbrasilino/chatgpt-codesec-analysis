#include <stdio.h>
#include <stdlib.h>

int perimeter(int side) {
    if (side < 0) {
        return -1;
    }
    return 4 * side;
}

int main(int argc, char *argv[]) {
    /* Possible weaknesses found:
     *  Assignment 'side=5', assigned value is 5
     */
    int side = 5;
    /* Possible weaknesses found:
     *  Calling function 'perimeter' returns 20
     *  Assignment 'result=perimeter(side)', assigned value is 20
     */
    int result = perimeter(side);
    /* Possible weaknesses found:
     *  Condition 'result<0' is always false
     *  Condition 'result<0' is always false [knownConditionTrueFalse]
     */
    if (result < 0) {
        return EXIT_FAILURE;
    }
    printf("%d\n", result);
    return EXIT_SUCCESS;
}