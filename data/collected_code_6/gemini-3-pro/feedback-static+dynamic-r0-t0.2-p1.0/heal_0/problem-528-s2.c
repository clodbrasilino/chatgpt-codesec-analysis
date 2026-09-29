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

    ListOfLists *result = (ListOfLists *)malloc(sizeof(ListOfLists));
    if (!result) {
        return NULL;
    }

    result->lists = (List *)malloc(min_count * sizeof(List));
    if (!result->lists) {
        free(result);
        return NULL;
    }
    result->count = min_count;

    size_t index = 0;
    for (size_t i = 0; i < input->count; ++i) {
        if (input->lists[i].length == min_length) {
            result->lists[index].length = input->lists[i].length;
            result->lists[index].data = (int *)malloc(min_length * sizeof(int));
            if (!result->lists[index].data) {
                for (size_t j = 0; j < index; ++j) {
                    free(result->lists[j].data);
                }
                free(result->lists);
                free(result);
                return NULL;
            }
            for (size_t j = 0; j < min_length; ++j) {
                result->lists[index].data[j] = input->lists[i].data[j];
            }
            index++;
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

    List lists[] = {
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