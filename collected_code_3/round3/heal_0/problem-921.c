#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
} Tuple;

Tuple* chunkTuples(Tuple *input, int size, int n, int *outputSize) {
    *outputSize = size / n;
    if (size % n != 0) {
        (*outputSize)++;
    }

    Tuple *output = (Tuple*)malloc(sizeof(Tuple) * (*outputSize));
    for (int i = 0; i < *outputSize; i++) {
        output[i].size = n;
        output[i].data = (int*)malloc(sizeof(int) * n);
        for (int j = 0; j < n && i * n + j < size; j++) {
            output[i].data[j] = input[i * n + j].data[0];
        }
    }

    return output;
}

int main() {
    int size = 10;
    int n = 3;
    Tuple *input = (Tuple*)malloc(sizeof(Tuple) * size);
    for (int i = 0; i < size; i++) {
        input[i].size = 1;
        input[i].data = (int*)malloc(sizeof(int));
        input[i].data[0] = i + 1;
    }

    int outputSize;
    Tuple *output = chunkTuples(input, size, n, &outputSize);

    for (int i = 0; i < outputSize; i++) {
        for (int j = 0; j < output[i].size; j++) {
            printf("%d ", output[i].data[j]);
        }
        printf("\n");
    }

    for (int i = 0; i < size; i++) {
        free(input[i].data);
    }
    free(input);

    for (int i = 0; i < outputSize; i++) {
        free(output[i].data);
    }
    free(output);

    return 0;
}