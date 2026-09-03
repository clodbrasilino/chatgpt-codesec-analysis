#include <stdio.h>
#include <stdlib.h>

int* find_common_indices(const int* list1, const int* list2, const int* list3, int size, int* common_count) {
    *common_count = 0;
    int* common_indices = (int*)malloc(size * sizeof(int));
    if (common_indices == NULL) return NULL;

    for (int i = 0; i < size; ++i) {
        if (list1[i] == list2[i] && list1[i] == list3[i]) {
            common_indices[(*common_count)++] = i;
        }
    }

    return common_indices;
}

int main() {
    /* Possible weaknesses found:
     *  Variable 'list1' can be declared as const array [constVariable]
     */
    int list1[] = {1, 2, 3, 4, 5};
    /* Possible weaknesses found:
     *  Variable 'list2' can be declared as const array [constVariable]
     */
    int list2[] = {1, 2, 6, 4, 7};
    /* Possible weaknesses found:
     *  Variable 'list3' can be declared as const array [constVariable]
     */
    int list3[] = {1, 2, 8, 4, 9};
    int size = 5;
    int common_count;

    int* common_indices = find_common_indices(list1, list2, list3, size, &common_count);

    if (common_indices != NULL) {
        for (int i = 0; i < common_count; ++i) {
            printf("%d ", common_indices[i]);
        }
        free(common_indices);
    } else {
        printf("Memory allocation failed\n");
    }

    return 0;
}