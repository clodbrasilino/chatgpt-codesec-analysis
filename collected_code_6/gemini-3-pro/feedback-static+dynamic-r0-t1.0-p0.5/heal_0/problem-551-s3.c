#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int **data;
    size_t rows;
    size_t *cols;
} NestedList;

int* extract_column(const NestedList *list, size_t col_index, size_t *out_size) {
    if (!list || !list->data || !list->cols || !out_size) {
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < list->rows; i++) {
        if (col_index < list->cols[i]) {
            count++;
        }
    }

    if (count == 0) {
        *out_size = 0;
        return NULL;
    }

    int *column_data = (int *)malloc(count * sizeof(int));
    if (!column_data) {
        return NULL;
    }

    size_t idx = 0;
    for (size_t i = 0; i < list->rows; i++) {
        if (col_index < list->cols[i]) {
            column_data[idx++] = list->data[i][col_index];
        }
    }

    *out_size = count;
    return column_data;
}

int main(void) {
    size_t rows = 3;
    size_t cols[] = {3, 2, 4};
    
    int *data[3];
    int row0[] = {1, 2, 3};
    int row1[] = {4, 5};
    int row2[] = {6, 7, 8, 9};
    
    data[0] = row0;
    data[1] = row1;
    data[2] = row2;

    NestedList list = {data, rows, cols};

    size_t col_index = 1;
    size_t out_size = 0;

    int *extracted = extract_column(&list, col_index, &out_size);

    if (extracted) {
        for (size_t i = 0; i < out_size; i++) {
            printf("%d ", extracted[i]);
        }
        printf("\n");
        free(extracted);
    } else {
        printf("Column extraction failed or column is empty.\n");
    }

    return 0;
}