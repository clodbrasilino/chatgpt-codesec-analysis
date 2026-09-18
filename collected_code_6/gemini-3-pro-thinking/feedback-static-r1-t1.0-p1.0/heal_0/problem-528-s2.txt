#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    int *data;
    size_t length;
} List;

typedef struct {
    List *lists;
    size_t count;
} ListOfLists;

typedef struct {
    const List **lists;
    size_t count;
} MinListsResult;

MinListsResult get_min_length_lists(const ListOfLists *input) {
    MinListsResult result = {NULL, 0};

    if (!input || !input->lists || input->count == 0) {
        return result;
    }

    size_t min_len = input->lists[0].length;
    for (size_t i = 1; i < input->count; ++i) {
        if (input->lists[i].length < min_len) {
            min_len = input->lists[i].length;
        }
    }

    size_t min_count = 0;
    for (size_t i = 0; i < input->count; ++i) {
        if (input->lists[i].length == min_len) {
            min_count++;
        }
    }

    result.lists = malloc(min_count * sizeof(const List *));
    if (!result.lists) {
        return result;
    }

    result.count = min_count;
    size_t index = 0;
    for (size_t i = 0; i < input->count; ++i) {
        if (input->lists[i].length == min_len) {
            result.lists[index++] = &input->lists[i];
        }
    }

    return result;
}

int main(void) {
    int data1[] = {1, 2, 3};
    int data2[] = {4};
    int data3[] = {5, 6};
    int data4[] = {7};

    List lists[4];
    lists[0].data = data1;
    lists[0].length = 3;
    
    lists[1].data = data2;
    lists[1].length = 1;
    
    lists[2].data = data3;
    lists[2].length = 2;
    
    lists[3].data = data4;
    lists[3].length = 1;

    ListOfLists lol = {lists, 4};

    MinListsResult res = get_min_length_lists(&lol);

    if (res.lists) {
        for (size_t i = 0; i < res.count; ++i) {
            if (res.lists[i] && res.lists[i]->data) {
                for (size_t j = 0; j < res.lists[i]->length; ++j) {
                    printf("%d ", res.lists[i]->data[j]);
                }
            }
            printf("\n");
        }
        free((void *)res.lists);
    }

    return 0;
}