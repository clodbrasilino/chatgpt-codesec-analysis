#include <stdio.h>
#include <stdlib.h>

int find_common_index(const int *list1, const int *list2, const int *list3, int length, int *result) {
    for (int i = 0; i < length; ++i) {
        if (list1[i] == list2[i] && list1[i] == list3[i]) {
            result[i] = list1[i];
        } else {
            result[i] = -1;
        }
    }
    return 0;
}

int main() {
    int len = 5;
    /* Possible weaknesses found:
     *  Variable 'list1' can be declared as const array [constVariable]
     */
    int list1[] = {1, 2, 3, 4, 5};
    /* Possible weaknesses found:
     *  Variable 'list2' can be declared as const array [constVariable]
     */
    int list2[] = {1, 8, 3, 7, 5};
    /* Possible weaknesses found:
     *  Variable 'list3' can be declared as const array [constVariable]
     */
    int list3[] = {1, 2, 3, 7, 5};
    int result[len];

    find_common_index(list1, list2, list3, len, result);

    for (int i = 0; i < len; ++i) {
        if (result[i] != -1) {
            printf("Common at index %d: %d\n", i, result[i]);
        }
    }

    return 0;
}