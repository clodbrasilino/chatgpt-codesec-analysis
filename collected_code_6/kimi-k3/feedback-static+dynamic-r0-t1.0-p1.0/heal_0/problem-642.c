#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    size_t cols;
} Row;

typedef struct {
    Row *rows;
    size_t count;
    size_t cols;
} Matrix;

static int compare_rows(const void *a, const void *b) {
    const Row *ra = (const Row *)a;
    const Row *rb = (const Row *)b;
    size_t i;
    
    for (i = 0; i < ra->cols; i++) {
        if (ra->data[i] < rb->data[i]) return -1;
        if (ra->data[i] > rb->data[i]) return 1;
    }
    return 0;
}

static int rows_equal(const Row *a, const Row *b) {
    size_t i;
    if (a->cols != b->cols) return 0;
    for (i = 0; i < a->cols; i++) {
        if (a->data[i] != b->data[i]) return 0;
    }
    return 1;
}

int remove_duplicate_rows(Matrix *mat) {
    size_t i, j;
    
    if (mat == NULL || mat->rows == NULL || mat->count == 0) {
        return -1;
    }
    
    qsort(mat->rows, mat->count, sizeof(Row), compare_rows);
    
    for (i = 0, j = 1; j < mat->count; j++) {
        if (!rows_equal(&mat->rows[i], &mat->rows[j])) {
            i++;
            if (i != j) {
                Row temp = mat->rows[i];
                mat->rows[i] = mat->rows[j];
                mat->rows[j] = temp;
            }
        }
    }
    
    mat->count = i + 1;
    return 0;
}

int init_matrix(Matrix *mat, size_t rows, size_t cols) {
    size_t i;
    
    if (mat == NULL || rows == 0 || cols == 0) {
        return -1;
    }
    
    mat->rows = (Row *)calloc(rows, sizeof(Row));
    if (mat->rows == NULL) {
        return -1;
    }
    
    mat->count = rows;
    mat->cols = cols;
    
    for (i = 0; i < rows; i++) {
        mat->rows[i].data = (int *)calloc(cols, sizeof(int));
        if (mat->rows[i].data == NULL) {
            size_t k;
            for (k = 0; k < i; k++) {
                free(mat->rows[k].data);
            }
            free(mat->rows);
            mat->rows = NULL;
            mat->count = 0;
            return -1;
        }
        mat->rows[i].cols = cols;
    }
    
    return 0;
}

void free_matrix(Matrix *mat) {
    size_t i;
    
    if (mat == NULL || mat->rows == NULL) {
        return;
    }
    
    for (i = 0; i < mat->count; i++) {
        free(mat->rows[i].data);
    }
    free(mat->rows);
    mat->rows = NULL;
    mat->count = 0;
    mat->cols = 0;
}

void print_matrix(const Matrix *mat) {
    size_t i, j;
    
    if (mat == NULL || mat->rows == NULL) {
        return;
    }
    
    for (i = 0; i < mat->count; i++) {
        printf("(");
        for (j = 0; j < mat->cols; j++) {
            printf("%d", mat->rows[i].data[j]);
            if (j < mat->cols - 1) {
                printf(", ");
            }
        }
        printf(")\n");
    }
}

int main(void) {
    Matrix mat;
    size_t i, j;
    int test_data[5][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {1, 2, 3},
        {7, 8, 9},
        {4, 5, 6}
    };
    
    if (init_matrix(&mat, 5, 3) != 0) {
        fprintf(stderr, "Failed to initialize matrix\n");
        return EXIT_FAILURE;
    }
    
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 3; j++) {
            mat.rows[i].data[j] = test_data[i][j];
        }
    }
    
    printf("Original matrix:\n");
    print_matrix(&mat);
    
    if (remove_duplicate_rows(&mat) != 0) {
        fprintf(stderr, "Failed to remove duplicates\n");
        free_matrix(&mat);
        return EXIT_FAILURE;
    }
    
    printf("\nMatrix after removing duplicates:\n");
    print_matrix(&mat);
    
    free_matrix(&mat);
    return EXIT_SUCCESS;
}