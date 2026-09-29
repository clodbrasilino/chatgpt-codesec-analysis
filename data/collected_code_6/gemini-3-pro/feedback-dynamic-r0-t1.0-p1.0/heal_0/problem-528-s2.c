#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct List {
    int* elements;
    int length;
};

struct ListOfLists {
    struct List* lists;
    int count;
};

struct ListOfLists find_min_length_lists(const struct ListOfLists* input) {
    struct ListOfLists result = {NULL, 0};
    if (!input || input->count == 0) {
        return result;
    }

    int min_length = INT_MAX;
    for (int i = 0; i < input->count; ++i) {
        if (input->lists[i].length < min_length) {
            min_length = input->lists[i].length;
        }
    }

    int count = 0;
    for (int i = 0; i < input->count; ++i) {
        if (input->lists[i].length == min_length) {
            count++;
        }
    }

    result.lists = (struct List*)malloc(count * sizeof(struct List));
    if (!result.lists) {
        return result;
    }

    result.count = count;
    int idx = 0;
    for (int i = 0; i < input->count; ++i) {
        if (input->lists[i].length == min_length) {
            result.lists[idx].length = input->lists[i].length;
            result.lists[idx].elements = (int*)malloc(min_length * sizeof(int));
            if (!result.lists[idx].elements) {
                for (int j = 0; j < idx; ++j) {
                    free(result.lists[j].elements);
                }
                free(result.lists);
                result.lists = NULL;
                result.count = 0;
                return result;
            }
            for (int k = 0; k < min_length; ++k) {
                result.lists[idx].elements[k] = input->lists[i].elements[k];
            }
            idx++;
        }
    }

    return result;
}

void free_list_of_lists(struct ListOfLists* lol) {
    if (lol && lol->lists) {
        for (int i = 0; i < lol->count; ++i) {
            free(lol->lists[i].elements);
        }
        free(lol->lists);
        lol->lists = NULL;
        lol->count = 0;
    }
}

int main(void) {
    int arr1[] = {1, 2, 3};
    int arr2[] = {4, 5};
    int arr3[] = {6};
    int arr4[] = {7};

    struct List lists[4];
    lists[0].elements = arr1; lists[0].length = 3;
    lists[1].elements = arr2; lists[1].length = 2;
    lists[2].elements = arr3; lists[2].length = 1;
    lists[3].elements = arr4; lists[3].length = 1;

    struct ListOfLists input = {lists, 4};

    struct ListOfLists result = find_min_length_lists(&input);

    for (int i = 0; i < result.count; ++i) {
        for (int j = 0; j < result.lists[i].length; ++j) {
            printf("%d ", result.lists[i].elements[j]);
        }
        printf("\n");
    }

    free_list_of_lists(&result);

    return 0;
}