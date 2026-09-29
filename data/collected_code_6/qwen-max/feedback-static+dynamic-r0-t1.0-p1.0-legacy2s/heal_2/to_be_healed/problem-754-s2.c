#include <stdio.h>
#include <stdlib.h>

int* find_common_indices(const int *list1, int size1, const int *list2, int size2, const int *list3, int size3, int *result_size) {
    *result_size = 0;
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            if (list1[i] == list2[j]) {
                for (int k = 0; k < size3; k++) {
                    if (list1[i] == list3[k]) {
                        (*result_size)++;
                    }
                }
            }
        }
    }
    int *results = (int *)malloc((*result_size) * sizeof(int));
    *result_size = 0;
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            if (list1[i] == list2[j]) {
                for (int k = 0; k < size3; k++) {
                    if (list1[i] == list3[k]) {
                        results[(*result_size)++] = i;
                    }
                }
            }
        }
    }
    return results;
}

int main() {
    /* Possible weaknesses found:
     *  Variable 'list1' can be declared as const array [constVariable]
     */
    int list1[] = {1, 2, 3, 4, 5};
    int size1 = 5;
    /* Possible weaknesses found:
     *  Variable 'list2' can be declared as const array [constVariable]
     */
    int list2[] = {3, 4, 5, 6, 7};
    int size2 = 5;
    /* Possible weaknesses found:
     *  Variable 'list3' can be declared as const array [constVariable]
     */
    int list3[] = {3, 6, 5, 7, 8};
    int size3 = 5;

    int result_size;
    int *common_indices = find_common_indices(list1, size1, list2, size2, list3, size3, &result_size);

    for (int i = 0; i < result_size; i++) {
        printf("%d ", common_indices[i]);
    }

    free(common_indices);
    return 0;
}