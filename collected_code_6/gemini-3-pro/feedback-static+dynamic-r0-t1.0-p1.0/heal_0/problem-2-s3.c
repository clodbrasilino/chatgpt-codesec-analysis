#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int head;
    int tail;
} Tuple;

void find_similar_elements(Tuple* list1, size_t size1, Tuple* list2, size_t size2, Tuple** result, size_t* result_size) {
    if (!list1 || !list2 || !result || !result_size) {
        return;
    }

    size_t max_results = size1 < size2 ? size1 : size2;
    *result = (Tuple*)malloc(max_results * sizeof(Tuple));
    if (!*result) {
        *result_size = 0;
        return;
    }

    *result_size = 0;

    for (size_t i = 0; i < size1; ++i) {
        for (size_t j = 0; j < size2; ++j) {
            if (list1[i].head == list2[j].head && list1[i].tail == list2[j].tail) {
                (*result)[*result_size].head = list1[i].head;
                (*result)[*result_size].tail = list1[i].tail;
                (*result_size)++;
                break;
            }
        }
    }
}

int main() {
    Tuple list1[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
    Tuple list2[] = {{3, 4}, {9, 10}, {5, 6}, {11, 12}};
    size_t size1 = sizeof(list1) / sizeof(list1[0]);
    size_t size2 = sizeof(list2) / sizeof(list2[0]);

    Tuple* result = NULL;
    size_t result_size = 0;

    find_similar_elements(list1, size1, list2, size2, &result, &result_size);

    if (result) {
        for (size_t i = 0; i < result_size; ++i) {
            printf("(%d, %d)\n", result[i].head, result[i].tail);
        }
        free(result);
        result = NULL;
    }

    return 0;
}