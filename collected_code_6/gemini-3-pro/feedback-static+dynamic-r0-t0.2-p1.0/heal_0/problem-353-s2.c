#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int **data;
    size_t rows;
    size_t cols;
} NestedList;

NestedList* create_nested_list(size_t rows, size_t cols) {
    NestedList *list = malloc(sizeof(NestedList));
    if (!list) return NULL;

    list->rows = rows;
    list->cols = cols;
    list->data = malloc(rows * sizeof(int*));
    if (!list->data) {
        free(list);
        return NULL;
    }

    for (size_t i = 0; i < rows; i++) {
        list->data[i] = malloc(cols * sizeof(int));
        if (!list->data[i]) {
            for (size_t j = 0; j < i; j++) {
                free(list->data[j]);
            }
            free(list->data);
            free(list);
            return NULL;
        }
    }
    return list;
}

void free_nested_list(NestedList *list) {
    if (!list) return;
    for (size_t i = 0; i < list->rows; i++) {
        free(list->data[i]);
    }
    free(list->data);
    free(list);
}

int remove_column(NestedList *list, size_t col_index) {
    if (!list || col_index >= list->cols) return -1;

    if (list->cols == 1) {
        for (size_t i = 0; i < list->rows; i++) {
            free(list->data[i]);
            list->data[i] = NULL;
        }
        list->cols = 0;
        return 0;
    }

    for (size_t i = 0; i < list->rows; i++) {
        int *new_row = malloc((list->cols - 1) * sizeof(int));
        if (!new_row) return -1;

        size_t new_col = 0;
        for (size_t j = 0; j < list->cols; j++) {
            if (j != col_index) {
                new_row[new_col++] = list->data[i][j];
            }
        }
        free(list->data[i]);
        list->data[i] = new_row;
    }
    list->cols--;
    return 0;
}

void print_nested_list(const NestedList *list) {
    if (!list) return;
    for (size_t i = 0; i < list->rows; i++) {
        for (size_t j = 0; j < list->cols; j++) {
            printf("%d ", list->data[i][j]);
        }
        printf("\n");
    }
}

int main(void) {
    size_t rows = 3;
    size_t cols = 4;
    NestedList *list = create_nested_list(rows, cols);
    if (!list) return 1;

    int val = 1;
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            list->data[i][j] = val++;
        }
    }

    if (remove_column(list, 1) == 0) {
        print_nested_list(list);
    }

    free_nested_list(list);
    return 0;
}