#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t length;
} IntList;

typedef struct {
    IntList *lists;
    size_t count;
} ListOfLists;

void free_list_of_lists(ListOfLists *lol) {
    if (!lol) {
        return;
    }
    if (lol->lists) {
        for (size_t i = 0; i < lol->count; i++) {
            free(lol->lists[i].data);
        }
        free(lol->lists);
    }
    free(lol);
}

ListOfLists *find_min_length_lists(const ListOfLists *input) {
    if (!input || !input->lists || input->count == 0) {
        return NULL;
    }

    size_t min_len = input->lists[0].length;
    for (size_t i = 1; i < input->count; i++) {
        if (input->lists[i].length < min_len) {
            min_len = input->lists[i].length;
        }
    }

    size_t min_count = 0;
    for (size_t i = 0; i < input->count; i++) {
        if (input->lists[i].length == min_len) {
            min_count++;
        }
    }

    ListOfLists *result = malloc(sizeof(ListOfLists));
    if (!result) {
        return NULL;
    }

    result->count = min_count;
    result->lists = malloc(min_count * sizeof(IntList));
    if (!result->lists) {
        free(result);
        return NULL;
    }

    size_t idx = 0;
    for (size_t i = 0; i < input->count; i++) {
        if (input->lists[i].length == min_len) {
            result->lists[idx].length = min_len;
            if (min_len > 0) {
                result->lists[idx].data = malloc(min_len * sizeof(int));
                if (!result->lists[idx].data) {
                    result->count = idx;
                    free_list_of_lists(result);
                    return NULL;
                }
                for (size_t j = 0; j < min_len; j++) {
                    result->lists[idx].data[j] = input->lists[i].data[j];
                }
            } else {
                result->lists[idx].data = NULL;
            }
            idx++;
        }
    }

    return result;
}

int main(void) {
    ListOfLists *input = malloc(sizeof(ListOfLists));
    if (!input) {
        return EXIT_FAILURE;
    }

    input->count = 3;
    input->lists = malloc(input->count * sizeof(IntList));
    if (!input->lists) {
        free(input);
        return EXIT_FAILURE;
    }

    const int data0[] = {1, 2, 3};
    const int data1[] = {4};
    const int data2[] = {5, 6};

    input->lists[0].length = 3;
    input->lists[0].data = malloc(3 * sizeof(int));
    if (!input->lists[0].data) {
        input->count = 0;
        free_list_of_lists(input);
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < 3; i++) {
        input->lists[0].data[i] = data0[i];
    }

    input->lists[1].length = 1;
    input->lists[1].data = malloc(1 * sizeof(int));
    if (!input->lists[1].data) {
        input->count = 1;
        free_list_of_lists(input);
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < 1; i++) {
        input->lists[1].data[i] = data1[i];
    }

    input->lists[2].length = 2;
    input->lists[2].data = malloc(2 * sizeof(int));
    if (!input->lists[2].data) {
        input->count = 2;
        free_list_of_lists(input);
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < 2; i++) {
        input->lists[2].data[i] = data2[i];
    }

    ListOfLists *min_lists = find_min_length_lists(input);
    if (!min_lists) {
        free_list_of_lists(input);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < min_lists->count; i++) {
        for (size_t j = 0; j < min_lists->lists[i].length; j++) {
            printf("%d ", min_lists->lists[i].data[j]);
        }
        printf("\n");
    }

    free_list_of_lists(min_lists);
    free_list_of_lists(input);

    return EXIT_SUCCESS;
}