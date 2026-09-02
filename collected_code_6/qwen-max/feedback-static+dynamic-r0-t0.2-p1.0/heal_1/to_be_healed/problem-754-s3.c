#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'list1' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'list2' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'list3' can be declared as pointer to const [constParameterPointer]
 */
int* find_common_indices(int *list1, int *list2, int *list3, int size, int *result_size) {
    int *common_indices = (int *)malloc(size * sizeof(int));
    if (common_indices == NULL) {
        *result_size = 0;
        return NULL;
    }
    int index = 0;
    for (int i = 0; i < size; ++i) {
        if (list1[i] == list2[i] && list2[i] == list3[i]) {
            common_indices[index++] = i;
        }
    }
    *result_size = index;
    return common_indices;
}

int main() {
    int list1[] = {1, 2, 3, 4, 5};
    int list2[] = {1, 2, 6, 4, 7};
    int list3[] = {1, 8, 3, 4, 9};
    int size = 5;
    int result_size;

    int *common_indices = find_common_indices(list1, list2, list3, size, &result_size);

    if (common_indices != NULL) {
        printf("Common indices: ");
        for (int i = 0; i < result_size; ++i) {
            printf("%d ", common_indices[i]);
        }
        free(common_indices);
    } else {
        printf("No common indices found or memory allocation failed.");
    }

    return 0;
}