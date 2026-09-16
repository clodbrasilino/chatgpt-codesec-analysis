#include <stdio.h>
#include <stdlib.h>

int* modulo_division(const int* list1, int size1, const int* list2, int size2, int* resultSize) {
    if (size1 != size2) return NULL;
    *resultSize = size1;
    int* result = (int*)malloc(size1 * sizeof(int));
    if (result == NULL) return NULL;
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
    int list1[] = {10, 20, 30, 40, 50};
    int list2[] = {3, 4, 5, 6, 7};
    int size1 = sizeof(list1) / sizeof(list1[0]);
    int size2 = sizeof(list2) / sizeof(list2[0]);
    int resultSize;

    int *result = modulo_division(list1, size1, list2, size2, &resultSize);
    if (result == NULL) {
        printf("Invalid input.\n");
        return 1;
    }
    
    for (int i = 0; i < resultSize; ++i) {
        printf("%d ", result[i]);
    }
    printf("\n");
    free(result);
    return 0;
}