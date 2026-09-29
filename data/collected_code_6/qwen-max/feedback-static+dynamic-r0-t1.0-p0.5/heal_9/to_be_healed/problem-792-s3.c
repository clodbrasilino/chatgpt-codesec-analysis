#include <stdio.h>
#include <stdlib.h>

int count_lists(int num_lists) {
    return (num_lists > 0) ? num_lists : -1;
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
     *  Condition 'result!=-1' is always true
     *  Condition 'result!=-1' is always true [knownConditionTrueFalse]
     */
    if (result != -1) {
        printf("Number of lists: %d\n", result);
    } else {
        printf("Invalid input\n");
    }
    return 0;
}