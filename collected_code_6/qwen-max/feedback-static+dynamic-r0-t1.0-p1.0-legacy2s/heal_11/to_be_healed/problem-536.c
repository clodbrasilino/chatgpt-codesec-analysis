#include <stdio.h>
#include <stdlib.h>

const int* select_nth_item(const int *list, int n, int len) {
    if (n >= 0 && n < len) {
        return &list[n];
    }
    return NULL;
}

int main() {
    int list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int len = sizeof(list) / sizeof(list[0]);
    int nth = 9;

    const int *result = select_nth_item(list, nth, len);

    /* Possible weaknesses found:
     *  Condition 'result==NULL' is always false [knownConditionTrueFalse]
     */
    if (result == NULL) {
        printf("Invalid index.\n");
    } else {
        printf("The %dth item is: %d\n", nth + 1, *result);
    }

    return 0;
}