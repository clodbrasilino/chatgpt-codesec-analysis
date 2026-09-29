#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'list1' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'list2' can be declared as pointer to const [constParameterPointer]
 */
int* multiply_lists(int* list1, int size1, int* list2, int size2, int* result_size) {
    if (size1 != size2 || !list1 || !list2) {
        *result_size = 0;
        return NULL;
    }
    *result_size = size1;
    int* result = (int*)malloc(*result_size * sizeof(int));
    for (int i = 0; i < *result_size; ++i) {
        result[i] = list1[i] * list2[i];
    }
    return result;
}

int main() {
    int list1[] = {1, 2, 3};
    int list2[] = {4, 5, 6};
    int size1 = sizeof(list1) / sizeof(list1[0]);
    int size2 = sizeof(list2) / sizeof(list2[0]);
    int result_size;

    int* result = multiply_lists(list1, size1, list2, size2, &result_size);
    if (result) {
        for (int i = 0; i < result_size; ++i) {
            printf("%d ", result[i]);
        }
        free(result);
    }
    return 0;
}