#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct {
    int *values;
    size_t length;
} Tuple;

typedef struct {
    Tuple *rows;
    size_t count;
} TupleMatrix;

static bool tuples_equal(const Tuple *a, const Tuple *b)
{
    if (a == NULL || b == NULL || a->length != b->length) {
        return false;
    }

    if (a->length > 0U && (a->values == NULL || b->values == NULL)) {
        return false;
    }

    for (size_t i = 0U; i < a->length; ++i) {
        if (a->values[i] != b->values[i]) {
            return false;
        }
    }

    return true;
}

static int remove_similar_rows(TupleMatrix *matrix)
{
    if (matrix == NULL ||
        (matrix->count > 0U && matrix->rows == NULL)) {
        return -1;
    }

    size_t write_index = 0U;

    for (size_t read_index = 0U; read_index < matrix->count; ++read_index) {
        bool duplicate = false;

        if (matrix->rows[read_index].length > 0U &&
            matrix->rows[read_index].values == NULL) {
            return -1;
        }

        for (size_t unique_index = 0U;
             unique_index < write_index;
             ++unique_index) {
            if (tuples_equal(&matrix->rows[read_index],
                             &matrix->rows[unique_index])) {
                duplicate = true;
                break;
            }
        }

        if (duplicate) {
            free(matrix->rows[read_index].values);
            matrix->rows[read_index].values = NULL;
            matrix->rows[read_index].length = 0U;
        } else {
            if (write_index != read_index) {
                matrix->rows[write_index] = matrix->rows[read_index];
                matrix->rows[read_index].values = NULL;
                matrix->rows[read_index].length = 0U;
            }

            ++write_index;
        }
    }

    matrix->count = write_index;
    return 0;
}

static void free_matrix(TupleMatrix *matrix)
{
    if (matrix == NULL) {
        return;
    }

    if (matrix->rows != NULL) {
        for (size_t i = 0U; i < matrix->count; ++i) {
            free(matrix->rows[i].values);
            matrix->rows[i].values = NULL;
            matrix->rows[i].length = 0U;
        }

        free(matrix->rows);
        matrix->rows = NULL;
    }

    matrix->count = 0U;
}

static int read_matrix(TupleMatrix *matrix)
{
    size_t row_count;

    if (matrix == NULL) {
        return -1;
    }

    matrix->rows = NULL;
    matrix->count = 0U;

    if (scanf("%zu", &row_count) != 1) {
        return -1;
    }

    if (row_count > SIZE_MAX / sizeof(*matrix->rows)) {
        return -1;
    }

    if (row_count == 0U) {
        return 0;
    }

    matrix->rows = calloc(row_count, sizeof(*matrix->rows));
    if (matrix->rows == NULL) {
        return -1;
    }

    matrix->count = row_count;

    for (size_t i = 0U; i < row_count; ++i) {
        size_t length;

        if (scanf("%zu", &length) != 1) {
            free_matrix(matrix);
            return -1;
        }

        if (length > SIZE_MAX / sizeof(*matrix->rows[i].values)) {
            free_matrix(matrix);
            return -1;
        }

        matrix->rows[i].length = length;

        if (length == 0U) {
            continue;
        }

        matrix->rows[i].values =
            malloc(length * sizeof(*matrix->rows[i].values));

        if (matrix->rows[i].values == NULL) {
            free_matrix(matrix);
            return -1;
        }

        for (size_t j = 0U; j < length; ++j) {
            if (scanf("%d", &matrix->rows[i].values[j]) != 1) {
                free_matrix(matrix);
                return -1;
            }
        }
    }

    return 0;
}

static int print_matrix(const TupleMatrix *matrix)
{
    if (matrix == NULL ||
        (matrix->count > 0U && matrix->rows == NULL)) {
        return -1;
    }

    if (printf("%zu\n", matrix->count) < 0) {
        return -1;
    }

    for (size_t i = 0U; i < matrix->count; ++i) {
        if (matrix->rows[i].length > 0U &&
            matrix->rows[i].values == NULL) {
            return -1;
        }

        if (printf("%zu", matrix->rows[i].length) < 0) {
            return -1;
        }

        for (size_t j = 0U; j < matrix->rows[i].length; ++j) {
            if (printf(" %d", matrix->rows[i].values[j]) < 0) {
                return -1;
            }
        }

        if (putchar('\n') == EOF) {
            return -1;
        }
    }

    return 0;
}

int main(void)
{
    TupleMatrix matrix = {NULL, 0U};
    int status = EXIT_FAILURE;

    if (read_matrix(&matrix) != 0) {
        fputs("Failed to read matrix.\n", stderr);
        goto cleanup;
    }

    if (remove_similar_rows(&matrix) != 0) {
        fputs("Failed to remove duplicate rows.\n", stderr);
        goto cleanup;
    }

    if (print_matrix(&matrix) != 0) {
        fputs("Failed to write matrix.\n", stderr);
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free_matrix(&matrix);
    return status;
}