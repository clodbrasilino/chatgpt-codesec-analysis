#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    int *data;
    size_t size;
} IntList;

typedef struct {
    IntList *lists;
    size_t count;
} ListOfLists;

bool are_lists_equal(const IntList *a, const IntList *b) {
    if (!a || !b) {
        return false;
    }
    if (a->size != b->size) {
        return false;
    }
    for (size_t i = 0; i < a->size; i++) {
        if (a->data[i] != b->data[i]) {
            return false;
        }
    }
    return true;
}

size_t count_unique_lists(const ListOfLists *lol) {
    if (!lol || !lol->lists || lol->count == 0) {
        return 0;
    }

    size_t unique_count = 0;

    for (size_t i = 0; i < lol->count; i++) {
        bool is_duplicate = false;
        for (size_t j = 0; j < i; j++) {
            if (are_lists_equal(&lol->lists[i], &lol->lists[j])) {
                is_duplicate = true;
                break;
            }
        }
        if (!is_duplicate) {
            unique_count++;
        }
    }

    return unique_count;
}

void free_list_of_lists(ListOfLists *lol) {
    if (!lol) {
        return;
    }
    if (lol->lists) {
        for (size_t i = 0; i < lol->count; i++) {
            free(lol->lists[i].data);
            lol->lists[i].data = NULL;
        }
        free(lol->lists);
        lol->lists = NULL;
    }
    lol->count = 0;
}

int main(void) {
    ListOfLists lol = {NULL, 0};
    lol.count = 4;
    lol.lists = calloc(lol.count, sizeof(IntList));

    if (!lol.lists) {
        return EXIT_FAILURE;
    }

    int arr1[] = {1, 2, 3};
    int arr2[] = {4, 5};
    int arr3[] = {1, 2, 3};
    int arr4[] = {1, 2, 4};

    lol.lists[0].size = sizeof(arr1) / sizeof(arr1[0]);
    lol.lists[0].data = malloc(sizeof(arr1));
    if (lol.lists[0].data) {
        memcpy(lol.lists[0].data, arr1, sizeof(arr1));
    } else {
        free_list_of_lists(&lol);
        return EXIT_FAILURE;
    }

    lol.lists[1].size = sizeof(arr2) / sizeof(arr2[0]);
    lol.lists[1].data = malloc(sizeof(arr2));
    if (lol.lists[1].data) {
        memcpy(lol.lists[1].data, arr2, sizeof(arr2));
    } else {
        free_list_of_lists(&lol);
        return EXIT_FAILURE;
    }

    lol.lists[2].size = sizeof(arr3) / sizeof(arr3[0]);
    lol.lists[2].data = malloc(sizeof(arr3));
    if (lol.lists[2].data) {
        memcpy(lol.lists[2].data, arr3, sizeof(arr3));
    } else {
        free_list_of_lists(&lol);
        return EXIT_FAILURE;
    }

    lol.lists[3].size = sizeof(arr4) / sizeof(arr4[0]);
    lol.lists[3].data = malloc(sizeof(arr4));
    if (lol.lists[3].data) {
        memcpy(lol.lists[3].data, arr4, sizeof(arr4));
    } else {
        free_list_of_lists(&lol);
        return EXIT_FAILURE;
    }

    printf("%zu\n", count_unique_lists(&lol));

    free_list_of_lists(&lol);

    return EXIT_SUCCESS;
}