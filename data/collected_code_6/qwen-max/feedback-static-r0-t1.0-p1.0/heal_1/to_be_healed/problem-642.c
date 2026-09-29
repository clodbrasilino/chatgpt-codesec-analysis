#include <stdio.h>
#include <stdlib.h>

typedef int (*CompareFunc)(const void *, const void *);

int compareTuples(const void *a, const void *b) {
    /* Possible weaknesses found:
     *  Variable 'tupleA' can be declared as pointer to const [constVariablePointer]
     */
    int *tupleA = *(int **)a;
    /* Possible weaknesses found:
     *  Variable 'tupleB' can be declared as pointer to const [constVariablePointer]
     */
    int *tupleB = *(int **)b;
    for (int i = 0; i < 3; i++) {
        if (tupleA[i] != tupleB[i]) {
            return tupleA[i] < tupleB[i] ? -1 : 1;
        }
    }
    return 0;
}

int **removeSimilarRows(int **matrix, int rows, int *newRowCount) {
    qsort(matrix, rows, sizeof(int *), (CompareFunc)compareTuples);

    int *uniqueIndex = (int *)malloc(rows * sizeof(int));
    if (!uniqueIndex) exit(EXIT_FAILURE);
    uniqueIndex[0] = 0;
    int uniqueCount = 1;

    for (int i = 1; i < rows; i++) {
        if (compareTuples(&matrix[uniqueIndex[uniqueCount - 1]], &matrix[i]) != 0) {
            uniqueIndex[uniqueCount++] = i;
        }
    }

    int **result = (int **)malloc(uniqueCount * sizeof(int *));
    if (!result) exit(EXIT_FAILURE);
    for (int i = 0; i < uniqueCount; i++) {
        result[i] = matrix[uniqueIndex[i]];
    }
    free(uniqueIndex);
    *newRowCount = uniqueCount;
    return result;
}

int main() {
    int data[] = {1, 2, 3, 1, 2, 3, 4, 5, 6, 4, 5, 6, 7, 8, 9};
    int rows = 5;
    int cols = 3;
    int **matrix = (int **)malloc(rows * sizeof(int *));
    if (!matrix) exit(EXIT_FAILURE);
    for (int i = 0; i < rows; i++) {
        matrix[i] = &data[i * cols];
    }

    int newRowCount;
    int **result = removeSimilarRows(matrix, rows, &newRowCount);

    for (int i = 0; i < newRowCount; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    free(matrix);
    free(result);
    return 0;
}