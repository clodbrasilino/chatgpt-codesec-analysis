#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} IntList;

IntList* create_list(size_t size) {
    IntList *list = (IntList*)malloc(sizeof(IntList));
    list->size = size;
    list->elements = (int*)malloc(size * sizeof(int));
    return list;
}

void free_list(IntList *list) {
    free(list->elements);
    free(list);
}

int sum_of_elements(const IntList *list) {
    int sum = 0;
    for (size_t i = 0; i < list->size; ++i) {
        sum += list->elements[i];
    }
    return sum;
}

IntList* find_max_sum_list(const IntList *lists, size_t count) {
    if (count == 0) {
        return NULL;
    }

    const IntList *max_list = lists;
    int max_sum = sum_of_elements(max_list);

    for (size_t i = 1; i < count; ++i) {
        int current_sum = sum_of_elements(&lists[i]);
        if (current_sum > max_sum) {
            max_sum = current_sum;
            max_list = &lists[i];
        }
    }

    IntList *result = (IntList*)malloc(sizeof(IntList));
    result->size = max_list->size;
    result->elements = (int*)malloc(result->size * sizeof(int));
    for (size_t i = 0; i < result->size; ++i) {
        result->elements[i] = max_list->elements[i];
    }
    return result;
}

int main() {
    IntList *list1 = create_list(3);
    list1->elements[0] = 1;
    list1->elements[1] = 2;
    list1->elements[2] = 3;

    IntList *list2 = create_list(4);
    list2->elements[0] = 4;
    list2->elements[1] = 5;
    list2->elements[2] = 6;
    list2->elements[3] = 7;

    IntList *lists[] = { *list1, *list2 };
    size_t count = 2;

    IntList *max_sum_list = find_max_sum_list(lists, count);

    if (max_sum_list) {
        printf("List with the highest sum: ");
        for (size_t i = 0; i < max_sum_list->size; ++i) {
            printf("%d ", max_sum_list->elements[i]);
        }
        printf("\n");
        free_list(max_sum_list);
    } else {
        printf("No lists provided.\n");
    }

    free_list(list1);
    free_list(list2);

    return 0;
}