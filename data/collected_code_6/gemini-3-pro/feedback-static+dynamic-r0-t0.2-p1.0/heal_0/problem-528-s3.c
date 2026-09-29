#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t length;
} List;

typedef struct {
    List *lists;
    size_t count;
} ListOfLists;

ListOfLists* find_min_length_lists(const ListOfLists *input) {
    if (!input || input->count == 0) {
        return NULL;
    }

    size_t min_length = input->lists[0].length;
    for (size_t i = 1; i < input->count; ++i) {
        if (input->lists[i].length < min_length) {
            min_length = input->lists[i].length;
        }
    }

    size_t min_count = 0;
    for (size_t i = 0; i < input->count; ++i) {
        if (input->lists[i].length == min_length) {
            min_count++;
        }
    }

    ListOfLists *result = malloc(sizeof(ListOfLists));
    if (!result) {
        return NULL;
    }

    result->lists = malloc(min_count * sizeof(List));
    if (!result->lists) {
        free(result);
        return NULL;
    }
    result->count = min_count;

    size_t idx = 0;
    for (size_t i = 0; i < input->count; ++i) {
        if (input->lists[i].length == min_length) {
            result->lists[idx].length = input->lists[i].length;
            result->lists[idx].data = malloc(min_length * sizeof(int));
            if (!result->lists[idx].data) {
                for (size_t j = 0; j < idx; ++j) {
                    free(result->lists[j].data);
                }
                free(result->lists);
                free(result);
                return NULL;
            }
            for (size_t k = 0; k < min_length; ++k) {
                result->lists[idx].data[k] = input->lists[i].data[k];
            }
            idx++;
        }
    }

    return result;
}

void free_list_of_lists(ListOfLists *lol) {
    if (lol) {
        if (lol->lists) {
            for (size_t i = 0; i < lol->count; ++i) {
                free(lol->lists[i].data);
            }
            free(lol->lists);
        }
        free(lol);
    }
}

int main(void) {
    int data1[] = {1, 2, 3};
    int data2[] = {4, 5};
    int data3[] = {6, 7, 8, 9};
    int data4[] = {10, 11};

    List lists[4] = {
        {data1, 3},
        {data2, 2},
        {data3, 4},
        {data4, 2}
    };

    ListOfLists input = {lists, 4};

    ListOfLists *result = find_min_length_lists(&input);

    if (result) {
        for (size_t i = 0; i < result->count; ++i) {
            for (size_t j = 0; j < result->lists[i].length; ++j) {
                printf("%d ", result->lists[i].data[j]);
            }
            printf("\n");
        }
        free_list_of_lists(result);
    }

    return 0;
}