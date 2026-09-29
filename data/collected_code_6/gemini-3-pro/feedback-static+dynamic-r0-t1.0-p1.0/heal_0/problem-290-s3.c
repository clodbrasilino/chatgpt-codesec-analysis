#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* data;
    size_t length;
} List;

typedef struct {
    List* lists;
    size_t count;
} ListOfLists;

ListOfLists* find_max_length_lists(const ListOfLists* input) {
    if (!input || !input->lists || input->count == 0) {
        return NULL;
    }

    size_t max_len = 0;
    for (size_t i = 0; i < input->count; i++) {
        if (input->lists[i].length > max_len) {
            max_len = input->lists[i].length;
        }
    }

    ListOfLists* result = (ListOfLists*)malloc(sizeof(ListOfLists));
    if (!result) {
        return NULL;
    }

    result->count = 0;
    for (size_t i = 0; i < input->count; i++) {
        if (input->lists[i].length == max_len) {
            result->count++;
        }
    }

    result->lists = (List*)malloc(result->count * sizeof(List));
    if (!result->lists) {
        free(result);
        return NULL;
    }

    size_t idx = 0;
    for (size_t i = 0; i < input->count; i++) {
        if (input->lists[i].length == max_len) {
            result->lists[idx].length = input->lists[i].length;
            result->lists[idx].data = (int*)malloc(input->lists[i].length * sizeof(int));
            if (!result->lists[idx].data) {
                for (size_t j = 0; j < idx; j++) {
                    free(result->lists[j].data);
                }
                free(result->lists);
                free(result);
                return NULL;
            }
            for (size_t k = 0; k < input->lists[i].length; k++) {
                result->lists[idx].data[k] = input->lists[i].data[k];
            }
            idx++;
        }
    }

    return result;
}

void free_list_of_lists(ListOfLists* lol) {
    if (!lol) return;
    for (size_t i = 0; i < lol->count; i++) {
        free(lol->lists[i].data);
    }
    free(lol->lists);
    free(lol);
}

int main(void) {
    List lists[3];
    int data1[] = {1, 2};
    lists[0].data = data1;
    lists[0].length = 2;

    int data2[] = {3, 4, 5};
    lists[1].data = data2;
    lists[1].length = 3;

    int data3[] = {6, 7, 8};
    lists[2].data = data3;
    lists[2].length = 3;

    ListOfLists input;
    input.lists = lists;
    input.count = 3;

    ListOfLists* result = find_max_length_lists(&input);
    
    if (result) {
        for (size_t i = 0; i < result->count; i++) {
            for (size_t j = 0; j < result->lists[i].length; j++) {
                printf("%d ", result->lists[i].data[j]);
            }
            printf("\n");
        }
        free_list_of_lists(result);
    }

    return 0;
}