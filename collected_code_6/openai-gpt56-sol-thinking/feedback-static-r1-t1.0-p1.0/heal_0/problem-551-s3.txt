#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const int *values;
    size_t length;
} IntRow;

typedef struct {
    const IntRow *rows;
    size_t row_count;
} NestedList;

typedef enum {
    EXTRACT_OK,
    EXTRACT_INVALID_ARGUMENT,
    EXTRACT_COLUMN_MISSING,
    EXTRACT_SIZE_OVERFLOW,
    EXTRACT_ALLOCATION_FAILED
} ExtractStatus;

ExtractStatus extract_column(const NestedList *list,
                             size_t column_index,
                             int **out_column,
                             size_t *out_count)
{
    int *result;
    size_t i;

    if (out_column == NULL || out_count == NULL) {
        return EXTRACT_INVALID_ARGUMENT;
    }

    *out_column = NULL;
    *out_count = 0;

    if (list == NULL ||
        (list->row_count > 0 && list->rows == NULL)) {
        return EXTRACT_INVALID_ARGUMENT;
    }

    for (i = 0; i < list->row_count; ++i) {
        const IntRow *row = &list->rows[i];

        if (row->length > 0 && row->values == NULL) {
            return EXTRACT_INVALID_ARGUMENT;
        }

        if (column_index >= row->length) {
            return EXTRACT_COLUMN_MISSING;
        }
    }

    if (list->row_count == 0) {
        return EXTRACT_OK;
    }

    if (list->row_count > SIZE_MAX / sizeof(*result)) {
        return EXTRACT_SIZE_OVERFLOW;
    }

    result = malloc(list->row_count * sizeof(*result));
    if (result == NULL) {
        return EXTRACT_ALLOCATION_FAILED;
    }

    for (i = 0; i < list->row_count; ++i) {
        result[i] = list->rows[i].values[column_index];
    }

    *out_column = result;
    *out_count = list->row_count;

    return EXTRACT_OK;
}

int main(void)
{
    const int row1[] = {1, 2, 3};
    const int row2[] = {4, 5, 6};
    const int row3[] = {7, 8, 9};
    const IntRow rows[] = {
        {row1, sizeof(row1) / sizeof(row1[0])},
        {row2, sizeof(row2) / sizeof(row2[0])},
        {row3, sizeof(row3) / sizeof(row3[0])}
    };
    const NestedList list = {
        rows,
        sizeof(rows) / sizeof(rows[0])
    };
    int *column = NULL;
    size_t column_count = 0;
    size_t i;
    ExtractStatus status;

    status = extract_column(&list, 1, &column, &column_count);
    if (status != EXTRACT_OK) {
        switch (status) {
            case EXTRACT_INVALID_ARGUMENT:
                fputs("Invalid argument\n", stderr);
                break;
            case EXTRACT_COLUMN_MISSING:
                fputs("The requested column is missing from a row\n", stderr);
                break;
            case EXTRACT_SIZE_OVERFLOW:
                fputs("Requested allocation is too large\n", stderr);
                break;
            case EXTRACT_ALLOCATION_FAILED:
                fputs("Memory allocation failed\n", stderr);
                break;
            case EXTRACT_OK:
                break;
        }
        return EXIT_FAILURE;
    }

    for (i = 0; i < column_count; ++i) {
        if (printf("%d%s", column[i], i + 1 < column_count ? " " : "\n") < 0) {
            free(column);
            return EXIT_FAILURE;
        }
    }

    free(column);

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}