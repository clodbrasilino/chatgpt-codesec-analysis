#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    int value;
} Tuple;

Tuple* joinTuples(Tuple *arr1, int size1, Tuple *arr2, int size2, int *resultSize) {
    *resultSize = 0;
    Tuple *result = (Tuple*)malloc((size1 + size2) * sizeof(Tuple));
    if (!result) return NULL;

    for (int i = 0; i < size1; ++i) {
        for (int j = 0; j < size2; ++j) {
            if (arr1[i].key == arr2[j].key) {
                result[*resultSize].key = arr1[i].key;
                result[*resultSize].value = arr1[i].value + arr2[j].value;
                (*resultSize)++;
                break;
            }
        }
    }

    return result;
}

int main() {
    Tuple arr1[] = {{1, 10}, {2, 20}, {3, 30}};
    Tuple arr2[] = {{1, 40}, {2, 50}, {4, 60}};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    int resultSize;

    Tuple *result = joinTuples(arr1, size1, arr2, size2, &resultSize);

    if (result) {
        for (int i = 0; i < resultSize; ++i) {
            printf("(%d, %d)\n", result[i].key, result[i].value);
        }
        free(result);
    }

    return 0;
}