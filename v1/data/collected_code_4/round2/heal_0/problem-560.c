#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

void findTupleUnion(int tuple1[], int tuple2[], int size1, int size2) {
    int *result = (int*)malloc((size1 + size2) * sizeof(int));
    int i = 0, j = 0, k = 0;

    if(result == NULL) {
        printf("Memory allocation failed");
        return;
    }

    while(i < size1 && j < size2) {
        if(tuple1[i] < tuple2[j]) {
            result[k++] = tuple1[i++];
        } else if(tuple2[j] < tuple1[i]) {
            result[k++] = tuple2[j++];
        } else {
            result[k++] = tuple1[i++];
            ++j;
        }
    }

    while(i < size1) {
        result[k++] = tuple1[i++];
    }

    while(j < size2) {
        result[k++] = tuple2[j++];
    }

    for(i = 0; i < k; i++) {
        printf("%d ", result[i]);
    }

    free(result);
}

int main() {
    int tuple1[SIZE] = {1, 2, 3, 4, 5};
    int tuple2[SIZE] = {4, 5, 6, 7, 8};
    findTupleUnion(tuple1, tuple2, SIZE, SIZE);
    return 0;
}