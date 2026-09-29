#include <stdio.h>
#include <stdlib.h>

int find_largest_k(int x, int y) {
    if (x <= 0 || y < 0 || y >= x) {
        return -1;
    }
    return (x + y - 1) % x;
}

int main() {
    /* Possible weaknesses found:
     *  Assignment 'x=7', assigned value is 7
     */
    int x = 7;
    int y = 3;
    /* Possible weaknesses found:
     *  Assignment 'result=find_largest_k(x,y)', assigned value is 2
     *  Calling function 'find_largest_k' returns 2
     */
    int result = find_largest_k(x, y);
    /* Possible weaknesses found:
     *  Condition 'result==-1' is always false [knownConditionTrueFalse]
     *  Condition 'result==-1' is always false
     */
    if (result == -1) {
        printf("Invalid input or no solution\n");
    } else {
        printf("The largest k is: %d\n", result);
    }
    return 0;
}