#include <stdio.h>
#include <stdlib.h>

int* find_common_indices(const int* list1, const int* list2, const int* list3, int size, int* result_size) {
    *result_size = 0;
    int* common_indices = (int*)malloc(size * sizeof(int));
    if (common_indices == NULL) {
        return NULL;
    }

    for (int i = 0; i < size; ++i) {
        if (list1[i] == list2[i] && list1[i] == list3[i]) {
            common_indices[(*result_size)++] = i;
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
    int list2[] = {2, 2, 3, 4, 6};
    /* Possible weaknesses found:
     *  Variable 'list3' can be declared as const array [constVariable]
     */
    int list3[] = {2, 3, 3, 4, 7};
    int size = 5;
    int result_size;

    int* common_indices = find_common_indices(list1, list2, list3, size, &result_size);

    if (common_indices != NULL) {
        for (int i = 0; i < result_size; ++i) {
            printf("%d ", common_indices[i]);
        }
        free(common_indices);
    } else {
        printf("Memory allocation failed\n");
    }

    return 0;
}