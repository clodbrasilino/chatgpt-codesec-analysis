#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int **data;
    int rows;
    int cols;
} NestedList;

int* extract_column(const NestedList *list, int col_index, int *out_size) {
    if (list == NULL || list->data == NULL || out_size == NULL) {
        return NULL;
    }
    if (col_index < 0 || col_index >= list->cols) {
        return NULL;
    }

    int *column = (int *)malloc(list->rows * sizeof(int));
    if (column == NULL) {
        return NULL;
    }

    for (int i = 0; i < list->rows; i++) {
        if (list->data[i] == NULL) {
            free(column);
            return NULL;
        }
        column[i] = list->data[i][col_index];
    }

    *out_size = list->rows;
    return column;
}

int main(void) {
    int rows = 3;
    int cols = 4;
    
    NestedList list;
    list.rows = rows;
    list.cols = cols;
    list.data = (int **)malloc(rows * sizeof(int *));
    
    if (list.data == NULL) {
        return 1;
    }

    for (int i = 0; i < rows; i++) {
        list.data[i] = (int *)malloc(cols * sizeof(int));
        if (list.data[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(list.data[j]);
            }
            free(list.data);
            return 1;
        }
        for (int j = 0; j < cols; j++) {
            list.data[i][j] = (i * cols) + j;
        }
    }

    int out_size = 0;
    int col_to_extract = 2;
    int *extracted_col = extract_column(&list, col_to_extract, &out_size);

    if (extracted_col != NULL) {
        for (int i = 0; i < out_size; i++) {
            printf("%d\n", extracted_col[i]);
        }
        free(extracted_col);
    }

    for (int i = 0; i < rows; i++) {
        free(list.data[i]);
    }
    free(list.data);

    return 0;
}