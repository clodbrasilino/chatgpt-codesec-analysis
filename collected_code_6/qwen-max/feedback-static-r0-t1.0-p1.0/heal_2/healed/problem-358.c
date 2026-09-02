#include <stdio.h>
#include <stdlib.h>

int* modulo_lists(const int *list1, int size1, const int *list2, int size2, int *resultSize) {
    if (size1 != size2) return NULL;
    *resultSize = size1;
    int *result = (int *)malloc(size1 * sizeof(int));
    if (!result) return NULL;
    for (int i = 0; i < size1; ++i) {
        if (list2[i] == 0) {
            free(result);
            return NULL;
        }
        result[i] = list1[i] % list2[i];
    }
    return result;
}

int main() {
    const int listA[] = {10, 20, 30, 40};
    const int listB[] = {2, 3, 1, 5};
    int size = 4;
    int resultSize;
    int *result = modulo_lists(listA, size, listB, size, &resultSize);

    if (result) {
        for (int i = 0; i < resultSize; ++i) {
            printf("%d ", result[i]);
        }
        free(result);
    } else {
        printf("Error in modulo_lists");
    }

    return 0;
}