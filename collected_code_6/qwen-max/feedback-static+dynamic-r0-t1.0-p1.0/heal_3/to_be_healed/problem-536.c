#include <stdio.h>
#include <stdlib.h>

int* select_nth_item(int *list, int n, int len) {
    if (n < 0 || n >= len) {
        return NULL;
    }
    return &list[n];
}

int main() {
    int list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int len = sizeof(list) / sizeof(list[0]);
    /* Possible weaknesses found:
     *  Assignment 'nth=2', assigned value is 2
     */
    int nth = 2;

    const int *result = select_nth_item(list, nth, len);

    /* Possible weaknesses found:
     *  Condition 'nth>=len' is always false
     *  Condition 'nth<0' is always false [knownConditionTrueFalse]
     *  Condition 'nth>=len' is always false [knownConditionTrueFalse]
     *  Condition 'nth<0' is always false
     */
    if (nth < 0 || nth >= len) {
        printf("Invalid index.\n");
    } else {
        printf("The %dth item is: %d\n", nth + 1, *result);
    }

    return 0;
}