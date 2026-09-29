#include <stdio.h>
#include <stdlib.h>

const int* select_nth_item(const int *list, int n, int len) {
    if (n < 0 || n >= len) {
        return NULL;
    }
    return &list[n];
}

int main() {
    int list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int len = sizeof(list) / sizeof(list[0]);
    int nth = 10;

    /* Possible weaknesses found:
     *  Assignment 'result=select_nth_item(list,nth,len)', assigned value is 0
     *  Calling function 'select_nth_item' returns 0
     */
    const int *result = select_nth_item(list, nth, len);

    /* Possible weaknesses found:
     *  Condition 'result==NULL' is always true [knownConditionTrueFalse]
     *  Condition 'result==NULL' is always true
     */
    if (result == NULL) {
        printf("Invalid index.\n");
    } else {
        printf("The %dth item is: %d\n", nth + 1, *result);
    }

    return 0;
}