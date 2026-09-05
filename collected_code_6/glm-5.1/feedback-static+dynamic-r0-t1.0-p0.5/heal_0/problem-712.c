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

ListOfLists remove_duplicates(const ListOfLists *input) {
    ListOfLists result;
    result.len = 0;
    result.lists = NULL;

    for (size_t i = 0; i < input->len; i++) {
        bool is_duplicate = false;
        for (size_t j = 0; j < result.len; j++) {
            if (lists_equal(&input->lists[i], &result.lists[j])) {
                is_duplicate = true;
                break;
            }
        }

        if (!is_duplicate) {
            List *temp = realloc(result.lists, (result.len + 1) * sizeof(List));
            if (!temp) {
                for (size_t k = 0; k < result.len; k++) {
                    free(result.lists[k].data);
                }
                free(result.lists);
                result.lists = NULL;
                result.len = 0;
                return result;
            }
            result.lists = temp;

            result.lists[result.len].data = malloc(input->lists[i].len * sizeof(int));
            if (!result.lists[result.len].data && input->lists[i].len > 0) {
                for (size_t k = 0; k < result.len; k++) {
                    free(result.lists[k].data);
                }
                free(result.lists);
                result.lists = NULL;
                result.len = 0;
                return result;
            }

            for (size_t k = 0; k < input->lists[i].len; k++) {
                result.lists[result.len].data[k] = input->lists[i].data[k];
            }
            result.lists[result.len].len = input->lists[i].len;
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
    int d4[] = {7};
    int d5[] = {4, 5};

    List lists_arr[5];
    lists_arr[0].data = d1; lists_arr[0].len = 3;
    lists_arr[1].data = d2; lists_arr[1].len = 2;
    lists_arr[2].data = d3; lists_arr[2].len = 3;
    lists_arr[3].data = d4; lists_arr[3].len = 1;
    lists_arr[4].data = d5; lists_arr[4].len = 2;

    ListOfLists input;
    input.lists = lists_arr;
    input.len = 5;

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

    free_list_of_lists(&output);

    return 0;
}