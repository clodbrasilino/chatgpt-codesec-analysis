#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* data;
    int size;
} Tuple;

int* substract_tuples(Tuple t1, Tuple t2) {
    if (t1.size != t2.size) {
        return NULL;
    }
    int* result = (int*)malloc(t1.size * sizeof(int));
    if (result == NULL) {
        return NULL;
    }
    for (int i = 0; i < t1.size; ++i) {
        result[i] = t1.data[i] - t2.data[i];
    }
    return result;
}

int main() {
    int arr1[] = {5, 10, 15};
    int arr2[] = {1, 2, 3};
    Tuple t1 = {arr1, 3};
    Tuple t2 = {arr2, 3};

    int* result = substract_tuples(t1, t2);
    if (result != NULL) {
        for (int i = 0; i < t1.size; ++i) {
            printf("%d ", result[i]);
        }
        free(result);
    }
    return 0;
}