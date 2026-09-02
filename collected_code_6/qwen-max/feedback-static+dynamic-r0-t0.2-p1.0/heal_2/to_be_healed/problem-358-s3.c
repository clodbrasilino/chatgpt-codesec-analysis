#include <stdio.h>
#include <stdlib.h>

int* modulo_lists(const int* list1, int size1, const int* list2, int size2, int* result_size) {
    if (size1 != size2 || size1 == 0) {
        *result_size = 0;
        return NULL;
    }
    int* result = (int*)malloc(size1 * sizeof(int));
    if (result == NULL) {
        *result_size = 0;
        return NULL;
    }
    for (int i = 0; i < size1; ++i) {
        if (list2[i] == 0) {
            free(result);
            *result_size = 0;
            return NULL;
        }
        result[i] = list1[i] % list2[i];
    }
    *result_size = size1;
    return result;
}

int main() {
    /* Possible weaknesses found:
     *  Variable 'list1' can be declared as const array [constVariable]
     */
    int list1[] = {10, 20, 30};
    /* Possible weaknesses found:
     *  Variable 'list2' can be declared as const array [constVariable]
     */
    int list2[] = {3, 4, 5};
    int size1 = 3;
    int size2 = 3;
    int result_size;

    int* result = modulo_lists(list1, size1, list2, size2, &result_size);

    if (result != NULL) {
        for (int i = 0; i < result_size; ++i) {
            printf("%d ", result[i]);
        }
        free(result);
    } else {
        printf("Error in modulo operation.\n");
    }

    return 0;
}