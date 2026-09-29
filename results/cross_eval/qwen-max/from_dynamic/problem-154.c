#include <stdio.h>
#include <stdlib.h>

int** extract_elements(int **matrix, int rows, int cols, int element, int *out_rows) {
    int count = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (matrix[i][j] == element) {
                count++;
            }
        }
    }

    *out_rows = count;
    if (count == 0) {
        return NULL;
    }

    int **result = (int **)malloc(count * sizeof(int *));
    if (result == NULL) {
        return NULL;
    }

    int index = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (matrix[i][j] == element) {
                result[index] = (int *)malloc(2 * sizeof(int));
                if (result[index] == NULL) {
                    for (int k = 0; k < index; ++k) {
                        free(result[k]);
                    }
                    free(result);
                    return NULL;
                }
                result[index][0] = i;
                result[index][1] = j;
                index++;
            }
        }
    }

    return result;
}

void free_extracted_elements(int **result, int out_rows) {
    for (int i = 0; i < out_rows; ++i) {
        free(result[i]);
    }
    free(result);
}

int main() {
    int rows = 3;
    int cols = 4;
    int matrix[rows][cols] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 1, 2, 3}
    };
    int element = 1;

    int **list = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; ++i) {
        list[i] = (int *)malloc(cols * sizeof(int));
        for (int j = 0; j < cols; ++j) {
            list[i][j] = matrix[i][j];
        }
    }

    int out_rows;
    int **result = extract_elements(list, rows, cols, element, &out_rows);

    if (result != NULL) {
        for (int i = 0; i < out_rows; ++i) {
            printf("(%d, %d)\n", result[i][0], result[i][1]);
        }
        free_extracted_elements(result, out_rows);
    } else {
        printf("No elements found.\n");
    }

    for (int i = 0; i < rows; ++i) {
        free(list[i]);
    }
    free(list);

    return 0;
}