#include <stdio.h>
#include <stdlib.h>

int* find_common_indices(const int *list1, const int *list2, const int *list3, int size, int *common_count) {
    int *common = (int *)malloc(size * sizeof(int));
    if (common == NULL) return NULL;
    *common_count = 0;

    for (int i = 0; i < size; ++i) {
        if (list1[i] == list2[i] && list2[i] == list3[i]) {
            common[(*common_count)++] = i;
        }
    }

    return common;
}

int main() {
    const int list1[] = {1, 2, 3, 4, 5};
    const int list2[] = {1, 2, 6, 4, 7};
    const int list3[] = {1, 2, 7, 4, 8};
    int size = 5;
    int common_count;

    int *common_indices = find_common_indices(list1, list2, list3, size, &common_count);

    if (common_indices != NULL) {
        printf("Common indices: ");
        for (int i = 0; i < common_count; ++i) {
            printf("%d ", common_indices[i]);
        }
        free(common_indices);
    } else {
        printf("Failed to allocate memory.\n");
    }

    return 0;
}