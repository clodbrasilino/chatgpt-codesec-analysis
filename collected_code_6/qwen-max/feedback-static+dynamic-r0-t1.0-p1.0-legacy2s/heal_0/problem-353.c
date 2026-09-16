#include <stdio.h>
#include <stdlib.h>

typedef struct List {
    int *data;
    int size;
} List;

void freeList(List *list) {
    free(list->data);
    free(list);
}

List* createList(int size) {
    List *list = (List*)malloc(sizeof(List));
    list->data = (int*)malloc(size * sizeof(int));
    list->size = size;
    return list;
}

List** removeColumn(List **matrix, int numRows, int colToRemove) {
    if (colToRemove >= 0) {
        for (int i = 0; i < numRows; i++) {
            List *newRow = createList(matrix[i]->size - 1);
            int j = 0;
            for (int k = 0; k < matrix[i]->size; k++) {
                if (k != colToRemove) {
                    newRow->data[j++] = matrix[i]->data[k];
                }
            }
            freeList(matrix[i]);
            matrix[i] = newRow;
        }
    }
    return matrix;
}

int main() {
    int numRows = 3;
    int numCols = 4;
    List **matrix = (List**)malloc(numRows * sizeof(List*));

    for (int i = 0; i < numRows; i++) {
        matrix[i] = createList(numCols);
        for (int j = 0; j < numCols; j++) {
            matrix[i]->data[j] = i * numCols + j;
        }
    }

    int colToRemove = 2;
    matrix = removeColumn(matrix, numRows, colToRemove);

    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols - 1; j++) {
            printf("%d ", matrix[i]->data[j]);
        }
        printf("\n");
    }

    for (int i = 0; i < numRows; i++) {
        freeList(matrix[i]);
    }
    free(matrix);

    return 0;
}