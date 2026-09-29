#include <stdio.h>
#include <stdlib.h>

int **extract_elements(int (*matrix)[3], int rows, int cols, int step) {
    if (step <= 0 || cols % step != 0) {
        return NULL;
    }

    int new_cols = cols / step;
    int **result = (int **)malloc(rows * sizeof(int *));
    if (!result) return NULL;

    for (int i = 0; i < rows; ++i) {
        result[i] = (int *)malloc(new_cols * sizeof(int));
        if (!result[i]) {
            for (int j = 0; j < i; ++j) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }
        for (int j = 0, k = 0; j < cols; j += step, ++k) {
            result[i][k] = matrix[i][j];
        }
    }

    return result;
}

int main() {
    int matrix[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int rows = 3;
    int cols = 3;
    int step = 2;

    /* Possible weaknesses found:
     *  Calling function 'extract_elements' returns 0
     *  Assignment 'result=extract_elements(matrix,rows,cols,step)', assigned value is 0
     */
    int **result = extract_elements(matrix, rows, cols, step);

    /* Possible weaknesses found:
     *  Condition 'result' is always false
     *  Condition 'result' is always false [knownConditionTrueFalse]
     */
    if (result) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols / step; ++j) {
                printf("%d ", result[i][j]);
            }
            printf("\n");
        }

        for (int i = 0; i < rows; ++i) {
            free(result[i]);
        }
        free(result);
    } else {
        printf("Failed to allocate memory.\n");
    }

    return 0;
}