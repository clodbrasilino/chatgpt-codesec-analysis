#include <stdio.h>
#include <stdlib.h>

int *extract_column(int **matrix, size_t rows, const size_t *col_sizes, size_t col_index, size_t *out_count)
{
    int *result;
    size_t i;
    size_t count;

    if (matrix == NULL || col_sizes == NULL || out_count == NULL || rows == 0U) {
        return NULL;
    }

    count = 0U;
    for (i = 0U; i < rows; i++) {
        if (matrix[i] != NULL && col_index < col_sizes[i]) {
            count++;
        }
    }

    if (count == 0U) {
        *out_count = 0U;
        return NULL;
    }

    result = malloc(count * sizeof(int));
    if (result == NULL) {
        *out_count = 0U;
        return NULL;
    }

    count = 0U;
    for (i = 0U; i < rows; i++) {
        if (matrix[i] != NULL && col_index < col_sizes[i]) {
            result[count] = matrix[i][col_index];
            count++;
        }
    }

    *out_count = count;
    return result;
}

static void free_matrix(int **matrix, size_t rows)
{
    size_t i;

    if (matrix == NULL) {
        return;
    }
    for (i = 0U; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main(void)
{
    size_t rows = 3U;
    size_t cols = 4U;
    size_t i;
    size_t j;
    size_t count;
    int **matrix;
    size_t *col_sizes;
    int *first_col;
    int *third_col;

    matrix = malloc(rows * sizeof(int *));
    if (matrix == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    col_sizes = malloc(rows * sizeof(size_t));
    if (col_sizes == NULL) {
        free(matrix);
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0U; i < rows; i++) {
        matrix[i] = malloc(cols * sizeof(int));
        if (matrix[i] == NULL) {
            free_matrix(matrix, i);
            free(col_sizes);
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }
        col_sizes[i] = cols;
        for (j = 0U; j < cols; j++) {
            matrix[i][j] = (int)((i * cols) + j + 1U);
        }
    }

    first_col = extract_column(matrix, rows, col_sizes, 0U, &count);
    if (first_col != NULL) {
        printf("First column: ");
        for (i = 0U; i < count; i++) {
            printf("%d ", first_col[i]);
        }
        printf("\n");
        free(first_col);
    } else {
        printf("No elements found in first column\n");
    }

    third_col = extract_column(matrix, rows, col_sizes, 2U, &count);
    if (third_col != NULL) {
        printf("Third column: ");
        for (i = 0U; i < count; i++) {
            printf("%d ", third_col[i]);
        }
        printf("\n");
        free(third_col);
    } else {
        printf("No elements found in third column\n");
    }

    free_matrix(matrix, rows);
    free(col_sizes);

    return EXIT_SUCCESS;
}