#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
} Tuple;

Tuple* chunk_tuples(Tuple *input, int size, int n, int *out_size) {
    *out_size = size / n;
    if (size % n != 0) (*out_size)++;
    Tuple *output = (Tuple*)malloc((*out_size) * sizeof(Tuple));
    for (int i = 0; i < *out_size; i++) {
        output[i].size = n;
        output[i].data = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n && i*n+j < size; j++) {
            output[i].data[j] = input[i*n+j].data[0];
        }
    }
    return output;
}

int main() {
    int size = 10;
    Tuple *input = (Tuple*)malloc(size * sizeof(Tuple));
    for (int i = 0; i < size; i++) {
        input[i].size = 1;
        input[i].data = (int*)malloc(sizeof(int));
        input[i].data[0] = i+1;
    }
    int out_size;
    Tuple *output = chunk_tuples(input, size, 3, &out_size);
    for (int i = 0; i < out_size; i++) {
        for (int j = 0; j < output[i].size; j++) {
            printf("%d ", output[i].data[j]);
        }
        printf("\n");
    }
    for (int i = 0; i < size; i++) {
        free(input[i].data);
    }
    free(input);
    for (int i = 0; i < out_size; i++) {
        free(output[i].data);
    }
    free(output);
    return 0;
}