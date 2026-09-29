#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int **data;
    size_t rows;
    size_t *cols;
} NestedTuple;

static void free_nested_tuple(NestedTuple *nt) {
    if (nt == NULL) {
        return;
    }
    if (nt->data != NULL) {
        for (size_t i = 0; i < nt->rows; ++i) {
            free(nt->data[i]);
        }
        free(nt->data);
    }
    free(nt->cols);
    nt->data = NULL;
    nt->cols = NULL;
    nt->rows = 0;
}

static int init_nested_tuple(NestedTuple *nt, size_t rows, const size_t *cols) {
    if (nt == NULL || cols == NULL || rows == 0) {
        return -1;
    }
    nt->data = NULL;
    nt->cols = NULL;
    nt->rows = 0;

    nt->cols = malloc(rows * sizeof(*nt->cols));
    if (nt->cols == NULL) {
        return -1;
    }
    nt->data = calloc(rows, sizeof(*nt->data));
    if (nt->data == NULL) {
        free(nt->cols);
        nt->cols = NULL;
        return -1;
    }
    nt->rows = rows;

    for (size_t i = 0; i < rows; ++i) {
        nt->cols[i] = cols[i];
        if (cols[i] > 0) {
            nt->data[i] = malloc(cols[i] * sizeof(*nt->data[i]));
            if (nt->data[i] == NULL) {
                free_nested_tuple(nt);
                return -1;
            }
        }
    }
    return 0;
}

static int subtract_nested_tuples(const NestedTuple *a, const NestedTuple *b, NestedTuple *result) {
    if (a == NULL || b == NULL || result == NULL) {
        return -1;
    }
    if (a->rows != b->rows || a->rows == 0) {
        return -1;
    }
    if (init_nested_tuple(result, a->rows, a->cols) != 0) {
        return -1;
    }
    for (size_t i = 0; i < a->rows; ++i) {
        if (a->cols[i] != b->cols[i]) {
            free_nested_tuple(result);
            return -1;
        }
        for (size_t j = 0; j < a->cols[i]; ++j) {
            result->data[i][j] = a->data[i][j] - b->data[i][j];
        }
    }
    return 0;
}

int main(void) {
    NestedTuple a = {0}, b = {0}, result = {0};
    const size_t cols[] = {2, 3};
    const size_t rows = sizeof(cols) / sizeof(cols[0]);

    if (init_nested_tuple(&a, rows, cols) != 0) {
        return EXIT_FAILURE;
    }
    if (init_nested_tuple(&b, rows, cols) != 0) {
        free_nested_tuple(&a);
        return EXIT_FAILURE;
    }

    a.data[0][0] = 5; a.data[0][1] = 7;
    a.data[1][0] = 9; a.data[1][1] = 11; a.data[1][2] = 13;

    b.data[0][0] = 1; b.data[0][1] = 2;
    b.data[1][0] = 3; b.data[1][1] = 4;  b.data[1][2] = 5;

    if (subtract_nested_tuples(&a, &b, &result) != 0) {
        free_nested_tuple(&a);
        free_nested_tuple(&b);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < result.rows; ++i) {
        printf("(");
        for (size_t j = 0; j < result.cols[i]; ++j) {
            printf("%d%s", result.data[i][j], (j + 1 < result.cols[i]) ? ", " : "");
        }
        printf(")%s", (i + 1 < result.rows) ? ", " : "\n");
    }

    free_nested_tuple(&a);
    free_nested_tuple(&b);
    free_nested_tuple(&result);

    return EXIT_SUCCESS;
}