#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'list1' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'list2' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'list3' can be declared as pointer to const [constParameterPointer]
 */
int* find_common_indices(int* list1, int* list2, int* list3, int size, int* result_size) {
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
    int list1[] = {1, 2, 3, 4, 5};
    int list2[] = {2, 2, 3, 4, 6};
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