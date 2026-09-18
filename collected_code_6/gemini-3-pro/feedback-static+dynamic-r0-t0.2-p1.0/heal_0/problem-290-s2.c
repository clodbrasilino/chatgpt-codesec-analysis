#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t length;
} List;

typedef struct {
    List *lists;
    size_t count;
} ListOfLists;

ListOfLists find_max_length_lists(ListOfLists input) {
    ListOfLists result = {NULL, 0};
    if (input.count == 0 || input.lists == NULL) {
        return result;
    }

    size_t max_length = 0;
    for (size_t i = 0; i < input.count; ++i) {
        if (input.lists[i].length > max_length) {
            max_length = input.lists[i].length;
        }
    }

    size_t max_count = 0;
    for (size_t i = 0; i < input.count; ++i) {
        if (input.lists[i].length == max_length) {
            max_count++;
        }
    }

    result.lists = (List *)malloc(max_count * sizeof(List));
    if (result.lists == NULL) {
        return result;
    }

    result.count = max_count;
    size_t index = 0;
    for (size_t i = 0; i < input.count; ++i) {
        if (input.lists[i].length == max_length) {
            result.lists[index].length = input.lists[i].length;
            result.lists[index].elements = (int *)malloc(max_length * sizeof(int));
            if (result.lists[index].elements == NULL) {
                for (size_t j = 0; j < index; ++j) {
                    free(result.lists[j].elements);
                }
                free(result.lists);
                result.lists = NULL;
                result.count = 0;
                return result;
            }
            for (size_t j = 0; j < max_length; ++j) {
                result.lists[index].elements[j] = input.lists[i].elements[j];
            }
            index++;
        }
    }

    return result;
}

void free_list_of_lists(ListOfLists *lol) {
    if (lol != NULL && lol->lists != NULL) {
        for (size_t i = 0; i < lol->count; ++i) {
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
    int arr3[] = {6, 7, 8};
    int arr4[] = {9};

    List lists[4];
    lists[0].elements = arr1; lists[0].length = 3;
    lists[1].elements = arr2; lists[1].length = 2;
    lists[2].elements = arr3; lists[2].length = 3;
    lists[3].elements = arr4; lists[3].length = 1;

    ListOfLists input = {lists, 4};

    ListOfLists max_lists = find_max_length_lists(input);

    for (size_t i = 0; i < max_lists.count; ++i) {
        for (size_t j = 0; j < max_lists.lists[i].length; ++j) {
            printf("%d ", max_lists.lists[i].elements[j]);
        }
        printf("\n");
    }

    free_list_of_lists(&max_lists);

    return 0;
}