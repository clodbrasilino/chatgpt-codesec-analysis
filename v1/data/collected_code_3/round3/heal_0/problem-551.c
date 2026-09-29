#include <stdio.h>
#include <stdlib.h>

int** extractColumn(int** nestedList, int rows, int cols, int colToExtract, int* returnSize) {
    *returnSize = rows;
    int** column = (int**)malloc(rows * sizeof(int*));
    for(int i = 0; i < rows; i++) {
        column[i] = (int*)malloc(sizeof(int));
        *column[i] = nestedList[i][colToExtract];
    }
    return column;
}

int main() {
    int rows = 3, cols = 3;
    int** nestedList = (int**)malloc(rows * sizeof(int*));
    for(int i = 0; i < rows; i++) {
        nestedList[i] = (int*)malloc(cols * sizeof(int));
        for(int j = 0; j < cols; j++) {
            nestedList[i][j] = i * cols + j;
        }
    }

    int returnSize;
    int** column = extractColumn(nestedList, rows, cols, 1, &returnSize);

    for(int i = 0; i < returnSize; i++) {
        printf("%d ", *column[i]);
    }

    for(int i = 0; i < rows; i++) {
        free(nestedList[i]);
        free(column[i]);
    }
    free(nestedList);
    free(column);

    return 0;
}