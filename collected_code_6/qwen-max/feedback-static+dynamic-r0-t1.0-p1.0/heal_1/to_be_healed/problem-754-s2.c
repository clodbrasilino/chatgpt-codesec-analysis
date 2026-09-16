#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'list3' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'list1' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'list2' can be declared as pointer to const [constParameterPointer]
 */
int *find_common_indices(int *list1, int *list2, int *list3, int size1, int size2, int size3, int *return_size) {
    int *result = (int *)malloc(size1 * sizeof(int));
    if (result == NULL) {
        *return_size = 0;
        return NULL;
    }
    int k = 0;

    for (int i = 0; i < size1; ++i) {
        for (int j = 0; j < size2; ++j) {
            for (int l = 0; l < size3; ++l) {
                if (list1[i] == list2[j] && list1[i] == list3[l]) {
                    result[k++] = list1[i];
                }
            }
        }
    }

    *return_size = k;
    return result;
}

void free_result(int *result) {
    free(result);
}

int main() {
    int list1[] = {1, 2, 3, 4, 5};
    int list2[] = {3, 4, 5, 6, 7};
    int list3[] = {5, 6, 7, 8, 9};

    int size1 = sizeof(list1) / sizeof(list1[0]);
    int size2 = sizeof(list2) / sizeof(list2[0]);
    int size3 = sizeof(list3) / sizeof(list3[0]);

    int common_size;
    int *common_elements = find_common_indices(list1, list2, list3, size1, size2, size3, &common_size);

    if (common_elements == NULL) {
        printf("No common elements found.\n");
    } else {
        printf("Common elements: ");
        for (int i = 0; i < common_size; ++i) {
            printf("%d ", common_elements[i]);
        }
        printf("\n");
    }

    free_result(common_elements);

    return 0;
}