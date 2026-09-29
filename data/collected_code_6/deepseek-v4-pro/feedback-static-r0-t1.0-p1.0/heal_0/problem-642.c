#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int **data;
    int rows;
    int cols;
} TupleMatrix;

static int rows_equal(const int *row1, const int *row2, int cols) {
    return memcmp(row1, row2, cols * sizeof(int)) == 0;
}

static void free_matrix(int **matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

static int **allocate_matrix(int rows, int cols) {
    int **matrix = (int **)malloc(rows * sizeof(int *));
    if (!matrix) return NULL;
    
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
        if (!matrix[i]) {
            free_matrix(matrix, i);
            return NULL;
        }
    }
    return matrix;
}

TupleMatrix remove_similar_rows(const TupleMatrix *input) {
    TupleMatrix result = {NULL, 0, 0};
    
    if (!input || !input->data || input->rows <= 0 || input->cols <= 0) {
        return result;
    }
    
    int *keep_flags = (int *)calloc(input->rows, sizeof(int));
    if (!keep_flags) {
        return result;
    }
    
    int unique_count = 0;
    for (int i = 0; i < input->rows; i++) {
        int is_duplicate = 0;
        for (int j = 0; j < i; j++) {
            if (keep_flags[j] && rows_equal(input->data[i], input->data[j], input->cols)) {
                is_duplicate = 1;
                break;
            }
        }
        if (!is_duplicate) {
            keep_flags[i] = 1;
            unique_count++;
        }
    }
    
    result.data = allocate_matrix(unique_count, input->cols);
    if (!result.data) {
        free(keep_flags);
        return result;
    }
    
    result.rows = unique_count;
    result.cols = input->cols;
    
    int result_index = 0;
    for (int i = 0; i < input->rows; i++) {
        if (keep_flags[i]) {
            memcpy(result.data[result_index], input->data[i], input->cols * sizeof(int));
            result_index++;
        }
    }
    
    free(keep_flags);
    return result;
}

int main(void) {
    int rows = 5;
    int cols = 3;
    
    TupleMatrix matrix;
    matrix.rows = rows;
    matrix.cols = cols;
    matrix.data = allocate_matrix(rows, cols);
    
    if (!matrix.data) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    int test_data[5][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {1, 2, 3},
        {7, 8, 9},
        {4, 5, 6}
    };
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix.data[i][j] = test_data[i][j];
        }
    }
    
    TupleMatrix result = remove_similar_rows(&matrix);
    
    if (result.data) {
        printf("Rows: %d, Cols: %d\n", result.rows, result.cols);
        for (int i = 0; i < result.rows; i++) {
            for (int j = 0; j < result.cols; j++) {
                printf("%d ", result.data[i][j]);
            }
            printf("\n");
        }
        free_matrix(result.data, result.rows);
    } else {
        fprintf(stderr, "Failed to process matrix\n");
    }
    
    free_matrix(matrix.data, rows);
    return EXIT_SUCCESS;
}