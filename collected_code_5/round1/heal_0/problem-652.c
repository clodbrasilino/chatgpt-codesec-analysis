#include <stdio.h>
#include <stdlib.h>

typedef struct Tuple {
    int data[100];
    int size;
} Tuple;

Tuple* flatten_tuple_matrix(Tuple **matrix, int rows, int columns) {
    Tuple *result = (Tuple *)malloc(columns * sizeof(Tuple));
    if(result == NULL) return NULL;
    for(int i = 0; i < columns; i++) {
        result[i].size = 0;
    }
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            if(matrix[i][j].size + result[j].size > 100) return NULL;
            for(int k = 0; k < matrix[i][j].size; k++) {
                result[j].data[result[j].size++] = matrix[i][j].data[k];
            }
        }
    }
    return result;
}

int main() {
    Tuple **matrix = (Tuple **)malloc(3 * sizeof(Tuple *));
    for(int i = 0; i < 3; i++) {
        matrix[i] = (Tuple *)malloc(3 * sizeof(Tuple));
        for(int j = 0; j < 3; j++) {
            matrix[i][j].size = 0;
            for(int k = 0; k < 3; k++) {
                matrix[i][j].data[matrix[i][j].size++] = i + j + k;
            }
        }
    }
    Tuple *result = flatten_tuple_matrix(matrix, 3, 3);
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < result[i].size; j++) {
            printf("%d ", result[i].data[j]);
        }
        printf("\n");
    }
    for(int i = 0; i < 3; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(result);
    return 0;
}