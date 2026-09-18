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

ListOfLists* find_max_length_lists(const ListOfLists *input) {
    if (!input || input->count == 0 || !input->lists) {
        return NULL;
    }

    size_t max_length = 0;
    for (size_t i = 0; i < input->count; ++i) {
        if (input->lists[i].length > max_length) {
            max_length = input->lists[i].length;
        }
    }

    size_t max_count = 0;
    for (size_t i = 0; i < input->count; ++i) {
        if (input->lists[i].length == max_length) {
            max_count++;
        }
    }

    ListOfLists *result = malloc(sizeof(ListOfLists));
    if (!result) {
        return NULL;
    }

    result->lists = malloc(max_count * sizeof(List));
    if (!result->lists) {
        free(result);
        return NULL;
    }

    result->count = max_count;
    size_t idx = 0;
    for (size_t i = 0; i < input->count; ++i) {
        if (input->lists[i].length == max_length) {
            result->lists[idx].length = input->lists[i].length;
            result->lists[idx].data = malloc(max_length * sizeof(int));
            if (!result->lists[idx].data) {
                for (size_t j = 0; j < idx; ++j) {
                    free(result->lists[j].data);
                }
                free(result->lists);
                free(result);
                return NULL;
            }
            for (size_t j = 0; j < max_length; ++j) {
                result->lists[idx].data[j] = input->lists[i].data[j];
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
    ListOfLists input;
    input.count = 3;
    input.lists = malloc(3 * sizeof(List));
    if (!input.lists) {
        return 1;
    }

    input.lists[0].length = 2;
    input.lists[0].data = malloc(2 * sizeof(int));
    if (input.lists[0].data) {
        input.lists[0].data[0] = 1;
        input.lists[0].data[1] = 2;
    }

    input.lists[1].length = 3;
    input.lists[1].data = malloc(3 * sizeof(int));
    if (input.lists[1].data) {
        input.lists[1].data[0] = 3;
        input.lists[1].data[1] = 4;
        input.lists[1].data[2] = 5;
    }

    input.lists[2].length = 3;
    input.lists[2].data = malloc(3 * sizeof(int));
    if (input.lists[2].data) {
        input.lists[2].data[0] = 6;
        input.lists[2].data[1] = 7;
        input.lists[2].data[2] = 8;
    }

    ListOfLists *max_lists = find_max_length_lists(&input);

    if (max_lists) {
        for (size_t i = 0; i < max_lists->count; ++i) {
            for (size_t j = 0; j < max_lists->lists[i].length; ++j) {
                printf("%d ", max_lists->lists[i].data[j]);
            }
            printf("\n");
        }
        free_list_of_lists(max_lists);
    }

    for (size_t i = 0; i < input.count; ++i) {
        free(input.lists[i].data);
    }
    free(input.lists);

    return 0;
}