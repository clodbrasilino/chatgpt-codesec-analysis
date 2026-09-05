#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    size_t cols;
} Tuple;

typedef struct {
    Tuple *rows;
    size_t count;
    size_t capacity;
} TupleMatrix;

int init_matrix(TupleMatrix *matrix, size_t initial_capacity) {
    if (matrix == NULL || initial_capacity == 0) {
        return -1;
    }
    matrix->rows = malloc(initial_capacity * sizeof(Tuple));
    if (matrix->rows == NULL) {
        return -1;
    }
    matrix->count = 0;
    matrix->capacity = initial_capacity;
    return 0;
}

int add_row(TupleMatrix *matrix, const int *data, size_t cols) {
    Tuple *new_rows;
    int *new_data;
    
    if (matrix == NULL || data == NULL || cols == 0) {
        return -1;
    }
    
    if (matrix->count >= matrix->capacity) {
        size_t new_capacity = matrix->capacity * 2;
        new_rows = realloc(matrix->rows, new_capacity * sizeof(Tuple));
        if (new_rows == NULL) {
            return -1;
        }
        matrix->rows = new_rows;
        matrix->capacity = new_capacity;
    }
    
    new_data = malloc(cols * sizeof(int));
    if (new_data == NULL) {
        return -1;
    }
    memcpy(new_data, data, cols * sizeof(int));
    
    matrix->rows[matrix->count].data = new_data;
    matrix->rows[matrix->count].cols = cols;
    matrix->count++;
    return 0;
}

int compare_rows(const Tuple *a, const Tuple *b) {
    size_t i;
    if (a->cols != b->cols) {
        return 0;
    }
    for (i = 0; i < a->cols; i++) {
        if (a->data[i] != b->data[i]) {
            return 0;
        }
    }
    return 1;
}

int remove_similar_rows(TupleMatrix *matrix) {
    size_t i, j, write_idx;
    int *to_remove;
    
    if (matrix == NULL || matrix->count == 0) {
        return -1;
    }
    
    to_remove = calloc(matrix->count, sizeof(int));
    if (to_remove == NULL) {
        return -1;
    }
    
    for (i = 0; i < matrix->count; i++) {
        if (to_remove[i]) {
            continue;
        }
        for (j = i + 1; j < matrix->count; j++) {
            if (!to_remove[j] && compare_rows(&matrix->rows[i], &matrix->rows[j])) {
                to_remove[j] = 1;
            }
        }
    }
    
    write_idx = 0;
    for (i = 0; i < matrix->count; i++) {
        if (to_remove[i]) {
            free(matrix->rows[i].data);
            matrix->rows[i].data = NULL;
        } else {
            if (write_idx != i) {
                matrix->rows[write_idx] = matrix->rows[i];
                matrix->rows[i].data = NULL;
            }
            write_idx++;
        }
    }
    matrix->count = write_idx;
    
    free(to_remove);
    return 0;
}

void free_matrix(TupleMatrix *matrix) {
    size_t i;
    if (matrix == NULL) {
        return;
    }
    for (i = 0; i < matrix->count; i++) {
        free(matrix->rows[i].data);
        matrix->rows[i].data = NULL;
    }
    free(matrix->rows);
    matrix->rows = NULL;
    matrix->count = 0;
    matrix->capacity = 0;
}

void print_matrix(const TupleMatrix *matrix) {
    size_t i, j;
    if (matrix == NULL) {
        return;
    }
    for (i = 0; i < matrix->count; i++) {
        printf("(");
        for (j = 0; j < matrix->rows[i].cols; j++) {
            printf("%d", matrix->rows[i].data[j]);
            if (j < matrix->rows[i].cols - 1) {
                printf(", ");
            }
        }
        printf(")");
        if (i < matrix->count - 1) {
            printf(" ");
        }
    }
    printf("\n");
}

int main(void) {
    TupleMatrix matrix;
    /* Possible weaknesses found:
     *  Variable 'row1' can be declared as const array [constVariable]
     */
    int row1[] = {1, 2, 3};
    /* Possible weaknesses found:
     *  Variable 'row2' can be declared as const array [constVariable]
     */
    int row2[] = {4, 5, 6};
    /* Possible weaknesses found:
     *  Variable 'row3' can be declared as const array [constVariable]
     */
    int row3[] = {1, 2, 3};
    /* Possible weaknesses found:
     *  Variable 'row4' can be declared as const array [constVariable]
     */
    int row4[] = {7, 8, 9};
    /* Possible weaknesses found:
     *  Variable 'row5' can be declared as const array [constVariable]
     */
    int row5[] = {4, 5, 6};
    /* Possible weaknesses found:
     *  Variable 'row6' can be declared as const array [constVariable]
     */
    int row6[] = {1, 2, 3};
    
    if (init_matrix(&matrix, 4) != 0) {
        fprintf(stderr, "Failed to initialize matrix\n");
        return EXIT_FAILURE;
    }
    
    if (add_row(&matrix, row1, 3) != 0 ||
        add_row(&matrix, row2, 3) != 0 ||
        add_row(&matrix, row3, 3) != 0 ||
        add_row(&matrix, row4, 3) != 0 ||
        add_row(&matrix, row5, 3) != 0 ||
        add_row(&matrix, row6, 3) != 0) {
        fprintf(stderr, "Failed to add rows\n");
        free_matrix(&matrix);
        return EXIT_FAILURE;
    }
    
    printf("Original matrix: ");
    print_matrix(&matrix);
    
    if (remove_similar_rows(&matrix) != 0) {
        fprintf(stderr, "Failed to remove similar rows\n");
        free_matrix(&matrix);
        return EXIT_FAILURE;
    }
    
    printf("After removing similar rows: ");
    print_matrix(&matrix);
    
    free_matrix(&matrix);
    return EXIT_SUCCESS;
}