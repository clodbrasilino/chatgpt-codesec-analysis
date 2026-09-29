#include <stdio.h>
#include <stdlib.h>

int** extractColumn(int** nestedList, int rows, int cols, int colToExtract, int* returnSize) {
    if (nestedList == NULL) {
        return NULL;
    }

    *returnSize = rows;
    int** column = (int**)malloc(rows * sizeof(int*));
    if (column == NULL) {
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        column[i] = (int*)malloc(sizeof(int));

        if (column[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(column[j]);
            }
            free(column);
            return NULL;
        }

        /* Possible weaknesses found:
         *  leak of '<unknown>' [CWE-401] [-Wanalyzer-malloc-leak]
         */
        column[i] = &nestedList[i][colToExtract];
    }

    return column;
}

int main() {
    int rows = 3, cols = 3;
    int** nestedList = (int**)malloc(rows * sizeof(int*));

    if (nestedList == NULL) {
        return EXIT_FAILURE;
    }

    for(int i = 0; i < rows; i++) {
        nestedList[i] = (int*)malloc(cols * sizeof(int));
        
        if (nestedList[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(nestedList[j]);
            }
            free(nestedList);
            return EXIT_FAILURE;
        }

        for(int j = 0; j < cols; j++) {
            nestedList[i][j] = i * cols + j;
        }
    }

    int returnSize = 0;
    int** column = extractColumn(nestedList, rows, cols, 1, &returnSize);

    if (column == NULL) {
        for(int i = 0; i < rows; i++) {
            free(nestedList[i]);
        }
        free(nestedList);
        return EXIT_FAILURE;
    }

    for(int i = 0; i < returnSize; i++) {
        printf("%d ", *column[i]);
    }

    for(int i = 0; i < rows; i++) {
        free(nestedList[i]);
        free(column[i]);
    }

    free(nestedList);
    free(column);

    return EXIT_SUCCESS;
}