#include <stdio.h>
#include <stdlib.h>

int** create2DArray(int rows, int cols) {
    int **array = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; ++i) {
        array[i] = (int*)malloc(cols * sizeof(int));
    }
    return array;
}

void free2DArray(int **array, int rows) {
    for (int i = 0; i < rows; ++i) {
        free(array[i]);
    }
    free(array);
}

void fill2DArray(int **array, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            scanf("%d", &array[i][j]);
        }
    }
}

void print2DArray(int **array, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }
}

int* extractElements(int **array, int rows, int cols, int index) {
    int *result = (int*)malloc(rows * sizeof(int));
    for (int i = 0; i < rows; ++i) {
        result[i] = array[i][index];
    }
    return result;
}

int main() {
    int rows, cols, index;
    printf("Enter the number of rows: ");
    scanf("%d", &rows);
    printf("Enter the number of columns: ");
    scanf("%d", &cols);
    printf("Enter the index to extract (0-based): ");
    scanf("%d", &index);

    if (index < 0 || index >= cols) {
        printf("Index out of bounds.\n");
        return 1;
    }

    int **array = create2DArray(rows, cols);
    printf("Enter the elements of the 2D array:\n");
    fill2DArray(array, rows, cols);

    int *result = extractElements(array, rows, cols, index);
    printf("Extracted elements: ");
    for (int i = 0; i < rows; ++i) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
    free2DArray(array, rows);

    return 0;
}