#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int *values;
    size_t length;
} List;

typedef struct {
    List *rows;
    size_t row_count;
} NestedList;

typedef enum {
    LIST_SUCCESS,
    LIST_INVALID_ARGUMENT,
    LIST_OUT_OF_RANGE,
    LIST_ALLOCATION_FAILURE,
    LIST_IO_FAILURE
} ListStatus;

static void nested_list_destroy(NestedList *list)
{
    if (list == NULL) {
        return;
    }

    if (list->rows != NULL) {
        for (size_t i = 0; i < list->row_count; ++i) {
            free(list->rows[i].values);
            list->rows[i].values = NULL;
            list->rows[i].length = 0;
        }

        free(list->rows);
    }

    list->rows = NULL;
    list->row_count = 0;
}

static ListStatus nested_list_create(
    NestedList *out,
    const int *values,
    size_t value_count,
    size_t row_count,
    size_t column_count)
{
    size_t required_count;

    if (out == NULL) {
        return LIST_INVALID_ARGUMENT;
    }

    out->rows = NULL;
    out->row_count = 0;

    if (row_count == 0) {
        return LIST_SUCCESS;
    }

    if (row_count > SIZE_MAX / sizeof(*out->rows)) {
        return LIST_ALLOCATION_FAILURE;
    }

    if (column_count > SIZE_MAX / sizeof(*values)) {
        return LIST_ALLOCATION_FAILURE;
    }

    if (column_count != 0 && row_count > SIZE_MAX / column_count) {
        return LIST_ALLOCATION_FAILURE;
    }

    required_count = row_count * column_count;

    if (required_count != 0 && values == NULL) {
        return LIST_INVALID_ARGUMENT;
    }

    if (value_count < required_count) {
        return LIST_INVALID_ARGUMENT;
    }

    out->rows = calloc(row_count, sizeof(*out->rows));
    if (out->rows == NULL) {
        return LIST_ALLOCATION_FAILURE;
    }

    out->row_count = row_count;

    for (size_t i = 0; i < row_count; ++i) {
        List *row = &out->rows[i];

        row->length = column_count;

        if (column_count == 0) {
            continue;
        }

        row->values = malloc(column_count * sizeof(*row->values));
        if (row->values == NULL) {
            nested_list_destroy(out);
            return LIST_ALLOCATION_FAILURE;
        }

        for (size_t j = 0; j < column_count; ++j) {
            row->values[j] = values[i * column_count + j];
        }
    }

    return LIST_SUCCESS;
}

static ListStatus remove_column(NestedList *list, size_t column)
{
    if (list == NULL || (list->row_count != 0 && list->rows == NULL)) {
        return LIST_INVALID_ARGUMENT;
    }

    if (list->row_count == 0) {
        return LIST_OUT_OF_RANGE;
    }

    for (size_t i = 0; i < list->row_count; ++i) {
        const List *row = &list->rows[i];

        if (row->length != 0 && row->values == NULL) {
            return LIST_INVALID_ARGUMENT;
        }

        if (column >= row->length) {
            return LIST_OUT_OF_RANGE;
        }

        if (row->length > SIZE_MAX / sizeof(*row->values)) {
            return LIST_INVALID_ARGUMENT;
        }
    }

    for (size_t i = 0; i < list->row_count; ++i) {
        List *row = &list->rows[i];

        for (size_t j = column; j + 1 < row->length; ++j) {
            row->values[j] = row->values[j + 1];
        }

        --row->length;
    }

    return LIST_SUCCESS;
}

static ListStatus nested_list_print(const NestedList *list)
{
    if (list == NULL || (list->row_count != 0 && list->rows == NULL)) {
        return LIST_INVALID_ARGUMENT;
    }

    for (size_t i = 0; i < list->row_count; ++i) {
        if (list->rows[i].length != 0 &&
            list->rows[i].values == NULL) {
            return LIST_INVALID_ARGUMENT;
        }
    }

    for (size_t i = 0; i < list->row_count; ++i) {
        if (putchar('[') == EOF) {
            return LIST_IO_FAILURE;
        }

        for (size_t j = 0; j < list->rows[i].length; ++j) {
            if (j != 0 && fputs(", ", stdout) == EOF) {
                return LIST_IO_FAILURE;
            }

            if (printf("%d", list->rows[i].values[j]) < 0) {
                return LIST_IO_FAILURE;
            }
        }

        if (fputs("]\n", stdout) == EOF) {
            return LIST_IO_FAILURE;
        }
    }

    if (fflush(stdout) == EOF) {
        return LIST_IO_FAILURE;
    }

    return LIST_SUCCESS;
}

int main(void)
{
    const int values[] = {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12
    };
    NestedList list = {NULL, 0};
    ListStatus status;

    status = nested_list_create(
        &list,
        values,
        sizeof(values) / sizeof(values[0]),
        3,
        4);

    if (status != LIST_SUCCESS) {
        fputs("Failed to create nested list\n", stderr);
        return EXIT_FAILURE;
    }

    status = remove_column(&list, 1);
    if (status != LIST_SUCCESS) {
        fputs("Failed to remove column\n", stderr);
        nested_list_destroy(&list);
        return EXIT_FAILURE;
    }

    status = nested_list_print(&list);
    if (status != LIST_SUCCESS) {
        fputs("Failed to print nested list\n", stderr);
        nested_list_destroy(&list);
        return EXIT_FAILURE;
    }

    nested_list_destroy(&list);
    return EXIT_SUCCESS;
}