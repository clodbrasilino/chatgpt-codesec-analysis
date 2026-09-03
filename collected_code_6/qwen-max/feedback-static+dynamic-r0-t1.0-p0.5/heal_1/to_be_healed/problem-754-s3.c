#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'list1' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'list3' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'list2' can be declared as pointer to const [constParameterPointer]
 */
int* find_common_indices(int *list1, int *list2, int *list3, int size, int *common_count) {
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
    int list1[] = {1, 2, 3, 4, 5};
    int list2[] = {1, 2, 6, 4, 7};
    int list3[] = {1, 2, 7, 4, 8};
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