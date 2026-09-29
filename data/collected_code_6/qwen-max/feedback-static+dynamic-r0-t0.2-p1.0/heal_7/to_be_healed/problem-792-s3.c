#include <stdio.h>
#include <stdlib.h>

int count_lists(int num_lists) {
    if (num_lists < 0) {
        return -1;
    }
    return num_lists;
}

int main() {
    /* Possible weaknesses found:
     *  Assignment 'num_lists=5', assigned value is 5
     */
    int num_lists = 5;
    /* Possible weaknesses found:
     *  Assignment 'result=count_lists(num_lists)', assigned value is 5
     *  Calling function 'count_lists' returns 5
     */
    int result = count_lists(num_lists);

    /* Possible weaknesses found:
     *  Condition 'result==-1' is always false [knownConditionTrueFalse]
     *  Condition 'result==-1' is always false
     */
    if (result == -1) {
        printf("Invalid input\n");
    } else {
        printf("Number of lists: %d\n", result);
    }

    return 0;
}