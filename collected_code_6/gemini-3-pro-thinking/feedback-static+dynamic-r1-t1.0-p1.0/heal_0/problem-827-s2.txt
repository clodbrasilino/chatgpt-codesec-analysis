#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int **data;
    size_t rows;
    size_t cols;
} ListOfLists;

ListOfLists* create_list_of_lists(size_t rows, size_t cols);
void destroy_list_of_lists(ListOfLists *list);
int sum_specific_column(const ListOfLists *list, size_t col_index, long long *out_sum);

ListOfLists* create_list_of_lists(size_t rows, size_t cols) {
    if (rows == 0 || cols == 0) {
        return NULL;
    }

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

    for (size_t i = 0; i < rows; ++i) {
        list->data[i] = malloc(cols * sizeof(int));
        if (!list->data[i]) {
            for (size_t j = 0; j < i; ++j) {
                free(list->data[j]);
            }
            free(list->data);
            free(list);
            return NULL;
        }
    }

    return list;
}

void destroy_list_of_lists(ListOfLists *list) {
    if (!list) {
        return;
    }

    if (list->data) {
        for (size_t i = 0; i < list->rows; ++i) {
            free(list->data[i]);
        }
        free(list->data);
    }
    free(list);
}

int sum_specific_column(const ListOfLists *list, size_t col_index, long long *out_sum) {
    if (!list || !list->data || !out_sum) {
        return -1;
    }

    if (col_index >= list->cols) {
        return -1;
    }

    long long sum = 0;
    for (size_t i = 0; i < list->rows; ++i) {
        if (!list->data[i]) {
            return -1;
        }
        sum += list->data[i][col_index];
    }

    *out_sum = sum;
    return 0;
}

int main(void) {
    size_t rows = 4;
    size_t cols = 5;
    
    ListOfLists *list = create_list_of_lists(rows, cols);
    if (!list) {
        fprintf(stderr, "Failed to allocate list of lists.\n");
        return EXIT_FAILURE;
    }

    int value = 1;
    for (size_t i = 0; i < list->rows; ++i) {
        for (size_t j = 0; j < list->cols; ++j) {
            list->data[i][j] = value++;
        }
    }

    size_t target_col = 2;
    long long column_sum = 0;

    if (sum_specific_column(list, target_col, &column_sum) != 0) {
        fprintf(stderr, "Failed to calculate the sum for column %zu.\n", target_col);
        destroy_list_of_lists(list);
        return EXIT_FAILURE;
    }

    printf("Sum of column %zu is: %lld\n", target_col, column_sum);

    destroy_list_of_lists(list);
    return EXIT_SUCCESS;
}