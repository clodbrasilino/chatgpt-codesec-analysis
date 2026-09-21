#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

typedef struct {
    Tuple *rows;
    size_t num_rows;
} TupleMatrix;

bool tuples_are_equal(const Tuple *a, const Tuple *b) {
    if (a->size != b->size) {
        return false;
    }
    for (size_t i = 0; i < a->size; i++) {
        if (a->elements[i] != b->elements[i]) {
            return false;
        }
    }
    return true;
}

TupleMatrix* remove_duplicate_rows(const TupleMatrix *matrix) {
    if (!matrix || !matrix->rows) {
        return NULL;
    }

    TupleMatrix *unique_matrix = malloc(sizeof(TupleMatrix));
    if (!unique_matrix) {
        return NULL;
    }

    unique_matrix->rows = malloc(matrix->num_rows * sizeof(Tuple));
    if (!unique_matrix->rows) {
        free(unique_matrix);
        return NULL;
    }
    unique_matrix->num_rows = 0;

    for (size_t i = 0; i < matrix->num_rows; i++) {
        bool is_duplicate = false;
        for (size_t j = 0; j < unique_matrix->num_rows; j++) {
            if (tuples_are_equal(&matrix->rows[i], &unique_matrix->rows[j])) {
                is_duplicate = true;
                break;
            }
        }

        if (!is_duplicate) {
            Tuple *new_row = &unique_matrix->rows[unique_matrix->num_rows];
            new_row->size = matrix->rows[i].size;
            new_row->elements = malloc(new_row->size * sizeof(int));
            if (!new_row->elements) {
                for (size_t k = 0; k < unique_matrix->num_rows; k++) {
                    free(unique_matrix->rows[k].elements);
                }
                free(unique_matrix->rows);
                free(unique_matrix);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(new_row->elements, matrix->rows[i].elements, new_row->size * sizeof(int));
            unique_matrix->num_rows++;
        }
    }

    if (unique_matrix->num_rows == 0) {
        free(unique_matrix->rows);
        unique_matrix->rows = NULL;
    } else {
        Tuple *temp_rows = realloc(unique_matrix->rows, unique_matrix->num_rows * sizeof(Tuple));
        if (temp_rows) {
            unique_matrix->rows = temp_rows;
        }
    }

    return unique_matrix;
}

void free_tuple_matrix(TupleMatrix *matrix) {
    if (matrix) {
        if (matrix->rows) {
            for (size_t i = 0; i < matrix->num_rows; i++) {
                free(matrix->rows[i].elements);
            }
            free(matrix->rows);
        }
        free(matrix);
    }
}

int main(void) {
    int row1_data[] = {1, 2, 3};
    int row2_data[] = {4, 5, 6};
    int row3_data[] = {1, 2, 3};
    int row4_data[] = {7, 8, 9};

    Tuple rows[] = {
        {row1_data, 3},
        {row2_data, 3},
        {row3_data, 3},
        {row4_data, 3}
    };

    TupleMatrix matrix = {rows, 4};

    TupleMatrix *unique_matrix = remove_duplicate_rows(&matrix);

    if (unique_matrix) {
        for (size_t i = 0; i < unique_matrix->num_rows; i++) {
            for (size_t j = 0; j < unique_matrix->rows[i].size; j++) {
                printf("%d ", unique_matrix->rows[i].elements[j]);
            }
            printf("\n");
        }
        free_tuple_matrix(unique_matrix);
    }

    return 0;
}