#include <stdio.h>
#include <stdlib.h>

int* find_common_indices(const int *list1, const int *list2, const int *list3, int size, int *result_size) {
    int *common = (int *)malloc(size * sizeof(int));
    if (common == NULL) return NULL;
    *result_size = 0;

    for (int i = 0; i < size; ++i) {
        if (list1[i] == list2[i] && list2[i] == list3[i]) {
            common[(*result_size)++] = i;
        }
    }

    return common;
}

int main() {
    const int list1[] = {1, 2, 3, 4, 5};
    const int list2[] = {1, 2, 6, 4, 7};
    const int list3[] = {1, 8, 3, 4, 9};
    int size = 5;
    int result_size;

    int *common_indices = find_common_indices(list1, list2, list3, size, &result_size);

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