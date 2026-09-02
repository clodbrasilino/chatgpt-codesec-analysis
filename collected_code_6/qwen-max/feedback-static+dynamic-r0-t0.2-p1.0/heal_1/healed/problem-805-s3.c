#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} List;

int sum_of_elements(const List *list) {
    int sum = 0;
    for (size_t i = 0; i < list->size; ++i) {
        sum += list->elements[i];
    }
    return sum;
}

List* find_max_sum_list(const List *lists, size_t num_lists) {
    if (num_lists == 0) {
        return NULL;
    }

    const List *max_list = &lists[0];
    int max_sum = sum_of_elements(max_list);

    for (size_t i = 1; i < num_lists; ++i) {
        int current_sum = sum_of_elements(&lists[i]);
        if (current_sum > max_sum) {
            max_sum = current_sum;
            max_list = &lists[i];
        }
    }

    List *result = (List *)malloc(sizeof(List));
    result->elements = (int *)malloc(max_list->size * sizeof(int));
    result->size = max_list->size;
    for (size_t i = 0; i < max_list->size; ++i) {
        result->elements[i] = max_list->elements[i];
    }
    return result;
}

void free_list(List *list) {
    free(list->elements);
    free(list);
}

int main() {
    List lists[] = {
        { (int[]) {1, 2, 3}, 3 },
        { (int[]) {4, 5, 6}, 3 },
        { (int[]) {7, 8, 9}, 3 }
    };
    size_t num_lists = sizeof(lists) / sizeof(lists[0]);

    List *max_sum_list = find_max_sum_list(lists, num_lists);
    if (max_sum_list != NULL) {
        printf("Max sum list: ");
        for (size_t i = 0; i < max_sum_list->size; ++i) {
            printf("%d ", max_sum_list->elements[i]);
        }
        printf("\n");
        free_list(max_sum_list);
    } else {
        printf("No lists provided.\n");
    }

    return 0;
}