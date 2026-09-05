#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *data;
    size_t len;
} List;

typedef struct {
    List *lists;
    size_t len;
} ListOfLists;

bool lists_equal(const List *a, const List *b) {
    if (a->len != b->len) {
        return false;
    }
    for (size_t i = 0; i < a->len; i++) {
        if (a->data[i] != b->data[i]) {
            return false;
        }
    }
    return true;
}

bool is_duplicate(const ListOfLists *lol, size_t current_index) {
    for (size_t i = 0; i < current_index; i++) {
        if (lists_equal(&lol->lists[i], &lol->lists[current_index])) {
            return true;
        }
    }
    return false;
}

ListOfLists remove_duplicates(const ListOfLists *input) {
    ListOfLists result;
    result.len = 0;
    result.lists = NULL;

    for (size_t i = 0; i < input->len; i++) {
        if (!is_duplicate(input, i)) {
            List *temp = realloc(result.lists, (result.len + 1) * sizeof(List));
            if (!temp) {
                for (size_t j = 0; j < result.len; j++) {
                    free(result.lists[j].data);
                }
                free(result.lists);
                result.lists = NULL;
                result.len = 0;
                return result;
            }
            result.lists = temp;

            result.lists[result.len].len = input->lists[i].len;
            result.lists[result.len].data = malloc(input->lists[i].len * sizeof(int));
            if (!result.lists[result.len].data && input->lists[i].len > 0) {
                for (size_t j = 0; j < result.len; j++) {
                    free(result.lists[j].data);
                }
                free(result.lists);
                result.lists = NULL;
                result.len = 0;
                return result;
            }

            for (size_t k = 0; k < input->lists[i].len; k++) {
                result.lists[result.len].data[k] = input->lists[i].data[k];
            }
            result.len++;
        }
    }
    return result;
}

void free_list_of_lists(ListOfLists *lol) {
    for (size_t i = 0; i < lol->len; i++) {
        free(lol->lists[i].data);
    }
    free(lol->lists);
    lol->lists = NULL;
    lol->len = 0;
}

int main(void) {
    int d1[] = {1, 2, 3};
    int d2[] = {4, 5};
    int d3[] = {1, 2, 3};
    int d4[] = {6};
    int d5[] = {4, 5};

    ListOfLists input;
    input.len = 5;
    input.lists = malloc(input.len * sizeof(List));
    if (!input.lists) {
        return EXIT_FAILURE;
    }

    input.lists[0].data = d1;
    input.lists[0].len = 3;
    input.lists[1].data = d2;
    input.lists[1].len = 2;
    input.lists[2].data = d3;
    input.lists[2].len = 3;
    input.lists[3].data = d4;
    input.lists[3].len = 1;
    input.lists[4].data = d5;
    input.lists[4].len = 2;

    ListOfLists output = remove_duplicates(&input);

    for (size_t i = 0; i < output.len; i++) {
        printf("[");
        for (size_t j = 0; j < output.lists[i].len; j++) {
            printf("%d", output.lists[i].data[j]);
            if (j < output.lists[i].len - 1) {
                printf(", ");
            }
        }
        printf("]\n");
    }

    free(input.lists);
    free_list_of_lists(&output);

    return EXIT_SUCCESS;
}