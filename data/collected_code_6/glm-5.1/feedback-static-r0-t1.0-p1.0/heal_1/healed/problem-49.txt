#include <stdio.h>
#include <stdlib.h>

int* extract_elements(int** matrix, int rows, const int* cols, int index) {
    if (matrix == NULL || rows <= 0 || cols == NULL || index < 0) {
        return NULL;
    }

    int* result = (int*)malloc(rows * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        if (matrix[i] == NULL) {
            free(result);
            return NULL;
        }
        if (index >= cols[i]) {
            free(result);
            return NULL;
        }
        result[i] = matrix[i][index];
    }

    return result;
}

int main() {
    int row0[] = {10, 20, 30};
    int row1[] = {40, 50, 60};
    int row2[] = {70, 80, 90};

    int rows = 3;
    const int cols[] = {3, 3, 3};

    int** matrix = (int**)malloc(rows * sizeof(int*));
    if (matrix == NULL) {
        return 1;
    }

    matrix[0] = row0;
    matrix[1] = row1;
    matrix[2] = row2;

    int index = 1;
    int* extracted = extract_elements(matrix, rows, cols, index);

    if (extracted != NULL) {
        for (int i = 0; i < rows; i++) {
            printf("%d ", extracted[i]);
        }
        printf("\n");
        free(extracted);
    }

    free(matrix);

    return 0;
}