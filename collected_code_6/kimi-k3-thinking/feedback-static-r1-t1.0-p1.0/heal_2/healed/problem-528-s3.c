#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    int *data;
    size_t length;
} IntList;

typedef struct {
    IntList *items;
    size_t count;
} ListOfLists;

void free_list_of_lists(ListOfLists *list_of_lists)
{
    if (list_of_lists == NULL) {
        return;
    }
    if (list_of_lists->items != NULL) {
        for (size_t i = 0; i < list_of_lists->count; i++) {
            free(list_of_lists->items[i].data);
            list_of_lists->items[i].data = NULL;
        }
        free(list_of_lists->items);
        list_of_lists->items = NULL;
    }
    list_of_lists->count = 0;
}

static void free_partial_items(IntList *items, size_t count)
{
    if (items == NULL) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        free(items[i].data);
        items[i].data = NULL;
    }
    free(items);
}

int find_min_length_lists(const ListOfLists *input, ListOfLists *result)
{
    if (input == NULL || result == NULL) {
        return -1;
    }

    result->items = NULL;
    result->count = 0;

    if (input->items == NULL || input->count == 0) {
        return -1;
    }

    for (size_t i = 0; i < input->count; i++) {
        if (input->items[i].length > SIZE_MAX / sizeof(int)) {
            return -1;
        }
        if (input->items[i].length > 0 && input->items[i].data == NULL) {
            return -1;
        }
    }

    size_t min_length = input->items[0].length;
    for (size_t i = 1; i < input->count; i++) {
        if (input->items[i].length < min_length) {
            min_length = input->items[i].length;
        }
    }

    size_t min_count = 0;
    for (size_t i = 0; i < input->count; i++) {
        if (input->items[i].length == min_length) {
            min_count++;
        }
    }

    IntList *items = calloc(min_count, sizeof(*items));
    if (items == NULL) {
        return -1;
    }

    size_t index = 0;
    for (size_t i = 0; i < input->count; i++) {
        if (input->items[i].length == min_length) {
            if (index >= min_count) {
                free_partial_items(items, index);
                return -1;
            }
            items[index].data = NULL;
            items[index].length = min_length;
            if (min_length > 0) {
                if (input->items[i].data == NULL ||
                    input->items[i].length != min_length) {
                    free_partial_items(items, index + 1);
                    return -1;
                }
                if (min_length > SIZE_MAX / sizeof(int)) {
                    free_partial_items(items, index + 1);
                    return -1;
                }
                size_t copy_bytes = min_length * sizeof(int);
                int *data_copy = malloc(copy_bytes);
                if (data_copy == NULL) {
                    free_partial_items(items, index + 1);
                    return -1;
                }
                memcpy(data_copy, input->items[i].data, copy_bytes);
                items[index].data = data_copy;
            }
            index++;
        }
    }

    result->items = items;
    result->count = min_count;
    return 0;
}

int main(void)
{
    int data1[] = { 1, 2, 3 };
    int data2[] = { 4, 5 };
    int data3[] = { 6, 7, 8, 9 };
    int data4[] = { 10, 11 };

    IntList lists[] = {
        { data1, sizeof(data1) / sizeof(data1[0]) },
        { data2, sizeof(data2) / sizeof(data2[0]) },
        { data3, sizeof(data3) / sizeof(data3[0]) },
        { data4, sizeof(data4) / sizeof(data4[0]) }
    };

    ListOfLists input = { lists, sizeof(lists) / sizeof(lists[0]) };
    ListOfLists result = { NULL, 0 };

    if (find_min_length_lists(&input, &result) != 0) {
        fprintf(stderr, "Error: could not determine the minimum length lists.\n");
        return EXIT_FAILURE;
    }

    if (result.count > 0 && result.items != NULL) {
        printf("Minimum length: %zu\n", result.items[0].length);
        printf("Number of lists with minimum length: %zu\n", result.count);
        for (size_t i = 0; i < result.count; i++) {
            printf("[");
            for (size_t j = 0; j < result.items[i].length; j++) {
                printf("%s%d", (j == 0) ? "" : ", ", result.items[i].data[j]);
            }
            printf("]\n");
        }
    }

    free_list_of_lists(&result);
    return EXIT_SUCCESS;
}