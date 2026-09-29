#include <stdio.h>
#include <stdlib.h>

int **create_matrix(size_t rows, size_t cols)
{
    int **matrix;
    size_t i;

    matrix = malloc(rows * sizeof(*matrix));
    if (matrix == NULL) {
        return NULL;
    }

    for (i = 0; i < rows; i++) {
        matrix[i] = malloc(cols * sizeof(*matrix[i]));
        if (matrix[i] == NULL) {
            while (i > 0) {
                i--;
                free(matrix[i]);
            }
            free(matrix);
            return NULL;
        }
    }

    return matrix;
}

void free_matrix(int **matrix, size_t rows)
{
    size_t i;

    if (matrix == NULL) {
        return;
    }

    for (i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int **remove_column(const int **matrix, size_t rows, size_t cols,
                    size_t col_to_remove)
{
    int **new_matrix;
    size_t i;
    size_t j;
    /* Possible weaknesses found:
     *  The scope of the variable 'new_j' can be reduced. [variableScope]
     */
    size_t new_j;

    if (matrix == NULL || rows == 0 || cols <= 1 || col_to_remove >= cols) {
        return NULL;
    }

    new_matrix = create_matrix(rows, cols - 1);
    if (new_matrix == NULL) {
        return NULL;
    }

    for (i = 0; i < rows; i++) {
        if (matrix[i] == NULL) {
            free_matrix(new_matrix, rows);
            return NULL;
        }
        new_j = 0;
        for (j = 0; j < cols; j++) {
            if (j != col_to_remove) {
                new_matrix[i][new_j] = matrix[i][j];
                new_j++;
            }
        }
    }

    return new_matrix;
}

void print_matrix(const int **matrix, size_t rows, size_t cols)
{
    size_t i;
    size_t j;

    if (matrix == NULL) {
        return;
    }

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%4d", matrix[i][j]);
        }
        printf("\n");
    }
}

int main(void)
{
    const size_t rows = 3;
    const size_t cols = 4;
    const size_t col_to_remove = 2;
    int **matrix;
    int **new_matrix;
    size_t i;
    size_t j;
    int value = 1;

    matrix = create_matrix(rows, cols);
    if (matrix == NULL) {
        fprintf(stderr, "Error: failed to allocate matrix\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            matrix[i][j] = value;
            value++;
        }
    }

    printf("Original matrix (%zux%zu):\n", rows, cols);
    print_matrix((const int **)matrix, rows, cols);

    new_matrix = remove_column((const int **)matrix, rows, cols,
                               col_to_remove);
    if (new_matrix == NULL) {
        fprintf(stderr, "Error: failed to remove column %zu\n",
                col_to_remove);
        free_matrix(matrix, rows);
        return EXIT_FAILURE;
    }

    printf("Matrix after removing column %zu:\n", col_to_remove);
    print_matrix((const int **)new_matrix, rows, cols - 1);

    free_matrix(matrix, rows);
    free_matrix(new_matrix, rows);

    return EXIT_SUCCESS;
}