#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int **data;
    size_t rows;
    size_t cols;
} ListOfLists;

typedef enum {
    SUCCESS = 0,
    ERROR_NULL_POINTER = 1,
    ERROR_OUT_OF_BOUNDS = 2
} ErrorCode;

ErrorCode sum_column(const ListOfLists *list, size_t col_index, long long *result) {
    if (!list || !list->data || !result) {
        return ERROR_NULL_POINTER;
    }
    if (col_index >= list->cols) {
        return ERROR_OUT_OF_BOUNDS;
    }

    long long sum = 0;
    for (size_t i = 0; i < list->rows; i++) {
        if (!list->data[i]) {
            return ERROR_NULL_POINTER;
        }
        sum += (long long)list->data[i][col_index];
    }

    *result = sum;
    return SUCCESS;
}

ListOfLists* create_list_of_lists(size_t rows, size_t cols) {
    ListOfLists *list = malloc(sizeof(ListOfLists));
    if (!list) {
        return NULL;
    }
    
    list->rows = rows;
    list->cols = cols;
    list->data = malloc(rows * sizeof(int *));
    
    if (!list->data) {
        free(list);
        return NULL;
    }
    
    for (size_t i = 0; i < rows; i++) {
        list->data[i] = calloc(cols, sizeof(int));
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

void free_list_of_lists(ListOfLists *list) {
    if (!list) {
        return;
    }
    if (list->data) {
        for (size_t i = 0; i < list->rows; i++) {
            free(list->data[i]);
        }
        free(list->data);
    }
    free(list);
}

int main(void) {
    size_t rows = 3;
    size_t cols = 4;
    
    ListOfLists *list = create_list_of_lists(rows, cols);
    if (!list) {
        return EXIT_FAILURE;
    }

    int counter = 1;
    for (size_t i = 0; i < list->rows; i++) {
        for (size_t j = 0; j < list->cols; j++) {
            list->data[i][j] = counter++;
        }
    }

    long long total = 0;
    size_t target_col = 2;
    ErrorCode status = sum_column(list, target_col, &total);

    if (status == SUCCESS) {
        printf("%lld\n", total);
    }

    free_list_of_lists(list);

    if (status != SUCCESS) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}