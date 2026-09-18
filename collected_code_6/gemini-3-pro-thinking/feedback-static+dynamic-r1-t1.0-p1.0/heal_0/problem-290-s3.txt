#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *elements;
    size_t length;
} List;

typedef struct {
    List *lists;
    size_t count;
} ListOfLists;

void free_list_of_lists(ListOfLists *lol) {
    if (!lol) {
        return;
    }
    if (lol->lists) {
        for (size_t i = 0; i < lol->count; i++) {
            free(lol->lists[i].elements);
        }
        free(lol->lists);
    }
    free(lol);
}

ListOfLists* get_max_length_lists(const ListOfLists *input) {
    if (!input || !input->lists || input->count == 0) {
        return NULL;
    }

    size_t max_len = 0;
    for (size_t i = 0; i < input->count; i++) {
        if (input->lists[i].length > max_len) {
            max_len = input->lists[i].length;
        }
    }

    size_t match_count = 0;
    for (size_t i = 0; i < input->count; i++) {
        if (input->lists[i].length == max_len) {
            match_count++;
        }
    }

    ListOfLists *result = (ListOfLists*)malloc(sizeof(ListOfLists));
    if (!result) {
        return NULL;
    }

    result->lists = (List*)calloc(match_count, sizeof(List));
    if (!result->lists) {
        free(result);
        return NULL;
    }
    result->count = match_count;

    size_t idx = 0;
    for (size_t i = 0; i < input->count; i++) {
        if (input->lists[i].length == max_len) {
            result->lists[idx].length = max_len;
            if (max_len > 0) {
                result->lists[idx].elements = (int*)malloc(max_len * sizeof(int));
                if (!result->lists[idx].elements) {
                    for (size_t j = 0; j < idx; j++) {
                        free(result->lists[j].elements);
                    }
                    free(result->lists);
                    free(result);
                    return NULL;
                }
                memcpy(result->lists[idx].elements, input->lists[i].elements, max_len * sizeof(int));
            } else {
                result->lists[idx].elements = NULL;
            }
            idx++;
        }
    }

    return result;
}

int init_list(List *list, const int *arr, size_t len) {
    list->length = len;
    if (len == 0) {
        list->elements = NULL;
        return 0;
    }
    list->elements = (int*)malloc(len * sizeof(int));
    if (!list->elements) {
        list->length = 0;
        return -1;
    }
    memcpy(list->elements, arr, len * sizeof(int));
    return 0;
}

int main(void) {
    ListOfLists input;
    input.count = 4;
    input.lists = (List*)calloc(input.count, sizeof(List));
    if (!input.lists) {
        return 1;
    }

    int arr1[] = {1, 2};
    int arr2[] = {3, 4, 5, 6};
    int arr3[] = {7, 8};
    int arr4[] = {9, 10, 11, 12};

    if (init_list(&input.lists[0], arr1, 2) != 0 ||
        init_list(&input.lists[1], arr2, 4) != 0 ||
        init_list(&input.lists[2], arr3, 2) != 0 ||
        init_list(&input.lists[3], arr4, 4) != 0) {
        
        for (size_t i = 0; i < input.count; i++) {
            free(input.lists[i].elements);
        }
        free(input.lists);
        return 1;
    }

    ListOfLists *result = get_max_length_lists(&input);
    if (result) {
        for (size_t i = 0; i < result->count; i++) {
            for (size_t j = 0; j < result->lists[i].length; j++) {
                printf("%d ", result->lists[i].elements[j]);
            }
            printf("\n");
        }
        free_list_of_lists(result);
    }

    for (size_t i = 0; i < input.count; i++) {
        free(input.lists[i].elements);
    }
    free(input.lists);

    return 0;
}