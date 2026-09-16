#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int *items;
    size_t length;
} List;

List **find_max_length_lists(List **lists, size_t num_lists, size_t *result_count) {
    if (result_count == NULL) {
        return NULL;
    }
    *result_count = 0;
    
    if (lists == NULL || num_lists == 0) {
        return NULL;
    }

    size_t max_length = 0;
    for (size_t i = 0; i < num_lists; i++) {
        if (lists[i] != NULL && lists[i]->length > max_length) {
            max_length = lists[i]->length;
        }
    }

    size_t count = 0;
    for (size_t i = 0; i < num_lists; i++) {
        if (lists[i] != NULL && lists[i]->length == max_length) {
            count++;
        }
    }

    if (count == 0) {
        return NULL;
    }

    if (count > SIZE_MAX / sizeof(List *)) {
        return NULL;
    }

    List **result = malloc(count * sizeof(List *));
    if (result == NULL) {
        return NULL;
    }

    size_t index = 0;
    for (size_t i = 0; i < num_lists; i++) {
        if (lists[i] != NULL && lists[i]->length == max_length) {
            result[index++] = lists[i];
        }
    }

    *result_count = count;
    return result;
}

int main(void) {
    int data1[] = {1, 2, 3};
    int data2[] = {4, 5};
    int data3[] = {6, 7, 8, 9};
    int data4[] = {10};

    List l1 = {data1, 3};
    List l2 = {data2, 2};
    List l3 = {data3, 4};
    List l4 = {data4, 1};

    List *array_of_lists[] = {&l1, &l2, &l3, &l4};
    size_t num_lists = sizeof(array_of_lists) / sizeof(array_of_lists[0]);

    size_t max_count = 0;
    List **max_lists = find_max_length_lists(array_of_lists, num_lists, &max_count);

    if (max_lists != NULL) {
        for (size_t i = 0; i < max_count; i++) {
            printf("List with max length (%zu): ", max_lists[i]->length);
            for (size_t j = 0; j < max_lists[i]->length; j++) {
                printf("%d ", max_lists[i]->items[j]);
            }
            printf("\n");
        }
        free(max_lists);
    }

    return 0;
}