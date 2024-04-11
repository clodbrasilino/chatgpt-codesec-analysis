#include <stdio.h>
#include <stdlib.h>

int** extractColumn(int** nestedList, int rows, int cols, int colToExtract, int* returnSize) {
    *returnSize = rows;
    int** column = (int**)malloc(rows * sizeof(int*));
    for(int i = 0; i < rows; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'column' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        column[i] = (int*)malloc(sizeof(int));
        /* Possible weaknesses found:
         *  dereference of possibly-NULL '*column_26 + _15' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        *column[i] = nestedList[i][colToExtract];
    }
    return column;
}

int main() {
    int rows = 3, cols = 3;
    int** nestedList = (int**)malloc(rows * sizeof(int*));
    for(int i = 0; i < rows; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'nestedList' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        nestedList[i] = (int*)malloc(cols * sizeof(int));
        for(int j = 0; j < cols; j++) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL '*nestedList_44 + _11 + (long unsigned int)j * 4' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
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