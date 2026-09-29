#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    int value;
} Tuple;

Tuple* joinTuples(Tuple* tuples1, int size1, Tuple* tuples2, int size2, int* resultSize) {
    *resultSize = 0;
    for (int i = 0; i < size1; ++i) {
        for (int j = 0; j < size2; ++j) {
            if (tuples1[i].key == tuples2[j].key) {
                (*resultSize)++;
                break;
            }
        }
    }

    Tuple* result = (Tuple*)malloc(*resultSize * sizeof(Tuple));
    if (result == NULL) {
        return NULL;
    }

    int index = 0;
    for (int i = 0; i < size1; ++i) {
        for (int j = 0; j < size2; ++j) {
            if (tuples1[i].key == tuples2[j].key) {
                result[index].key = tuples1[i].key;
                result[index].value = tuples1[i].value + tuples2[j].value;
                index++;
                break;
            }
        }
    }

    return result;
}

int main() {
    Tuple tuples1[] = {{1, 10}, {2, 20}, {3, 30}};
    Tuple tuples2[] = {{1, 100}, {2, 200}, {4, 400}};
    int size1 = sizeof(tuples1) / sizeof(tuples1[0]);
    int size2 = sizeof(tuples2) / sizeof(tuples2[0]);

    int resultSize;
    Tuple* result = joinTuples(tuples1, size1, tuples2, size2, &resultSize);

    if (result != NULL) {
        for (int i = 0; i < resultSize; ++i) {
            printf("(%d, %d)\n", result[i].key, result[i].value);
        }
        free(result);
    } else {
        printf("Memory allocation failed\n");
    }

    return 0;
}