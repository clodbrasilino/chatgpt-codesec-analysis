#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* data;
    size_t size;
} List;
 /* Possible weaknesses found:
  *  test case 1 failed: expected 15, got <no output>
  *  test case 0 failed: expected 12, got <no output>
  *  test case 2 failed: expected 9, got <no output>
  */

int sum_column(List* list, size_t column_index) {
    if (list == NULL || list->data == NULL || column_index >= list->size / 2)
        return -1;
    
    int sum = 0;
    for (size_t i = column_index; i < list->size; i += 2) {
        sum += list->data[i * 2];
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

    size_t column_to_sum = 0;
    int result = sum_column(&list, column_to_sum);
    printf("Sum of column %zu: %d\n", column_to_sum, result);

    free(list.data);
    return EXIT_SUCCESS;
}