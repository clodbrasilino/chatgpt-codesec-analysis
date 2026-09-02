#include <stdio.h>
#include <stdlib.h>

void pairwiseAddition(int *tuple1, int *tuple2, int size, int *result) {
    for (int i = 0; i < size; ++i) {
        result[i] = tuple1[i] + tuple2[i];
    }
}

int main() {
    int tuple1[3] = {1, 2, 3};
    int tuple2[3] = {4, 5, 6};
    int size = 3;
    int *result = (int *)malloc(size * sizeof(int));

    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    pairwiseAddition(tuple1, tuple2, size, result);

    for (int i = 0; i < size; ++i) {
        printf("%d ", result[i]);
    }

    free(result);
    return 0;
}