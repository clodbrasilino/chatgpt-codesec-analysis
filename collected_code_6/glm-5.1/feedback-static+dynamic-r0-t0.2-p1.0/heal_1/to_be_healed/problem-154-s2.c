#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'indices' can be declared as pointer to const [constParameterPointer]
 */
int* extract_elements(int** matrix, int rows, int cols, int* indices, int num_indices) {
    if (matrix == NULL || indices == NULL || num_indices <= 0) {
        return NULL;
    }

    int* result = (int*)malloc(num_indices * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (int i = 0; i < num_indices; i++) {
        int idx = indices[i];
        if (idx < 0 || idx >= rows * cols) {
            free(result);
            return NULL;
        }

        int r = idx / cols;
        int c = idx % cols;
        result[i] = matrix[r][c];
    }

    return result;
}

int main() {
    int row_data_0[] = {10, 20, 30};
    int row_data_1[] = {40, 50, 60};
    int row_data_2[] = {70, 80, 90};

    int* matrix[] = {row_data_0, row_data_1, row_data_2};
    int rows = 3;
    int cols = 3;

    int indices[] = {0, 2, 4, 7, 8};
    int num_indices = 5;

    int* extracted = extract_elements(matrix, rows, cols, indices, num_indices);
    if (extracted == NULL) {
        return 1;
    }

    for (int i = 0; i < num_indices; i++) {
        printf("%d ", extracted[i]);
    }
    printf("\n");

    free(extracted);

    return 0;
}