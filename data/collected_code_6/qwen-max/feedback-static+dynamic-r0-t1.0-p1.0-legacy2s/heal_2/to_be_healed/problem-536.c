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
    int nth = 2;

    const int *result = select_nth_item(list, nth, len);

    /* Possible weaknesses found:
     *  Condition 'result!=NULL' is always true [knownConditionTrueFalse]
     */
    if (result != NULL) {
        printf("The %dth item is: %d\n", nth + 1, *result);
    } else {
        printf("Invalid index.\n");
    }

    return 0;
}