#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* data;
    size_t size;
} List;

int sum_column(List* list, size_t column_index) {
    if (list == NULL || list->data == NULL || column_index >= list->size) {
        return -1;
    }

    int sum = 0;
    for (size_t i = column_index; i < list->size; i += 2) {
        sum += list->data[i];
    }
    return sum;
}

int main() {
    List list = {NULL, 0};
    const size_t row_size = 3;
    const size_t col_size = 2;
    list.size = row_size * col_size;
    list.data = (int*)malloc(list.size * sizeof(int));
    if (list.data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    int values[6] = {1, 2, 3, 4, 5, 6};
    for (size_t i = 0; i < list.size; ++i) {
        list.data[i] = values[i];
    }

    for (size_t col = 0; col < col_size; ++col) {
        int result = sum_column(&list, col);
        printf("Sum of column %zu: %d\n", col, result);
    }

    free(list.data);
    return EXIT_SUCCESS;
}