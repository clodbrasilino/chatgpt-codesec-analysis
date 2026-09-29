#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int *elements;
    size_t size;
} List;

typedef struct {
    List *lists;
    size_t count;
} ListOfLists;

const List* find_max_sum_list(const ListOfLists *lol);
void cleanup_list_of_lists(ListOfLists *lol);

const List* find_max_sum_list(const ListOfLists *lol) {
    if (!lol || !lol->lists || lol->count == 0) {
        return NULL;
    }

    const List *max_list = NULL;
    long long max_sum = 0;
    int has_valid_list = 0;

    for (size_t i = 0; i < lol->count; i++) {
        const List *current_list = &lol->lists[i];
        long long current_sum = 0;

        if (current_list->elements && current_list->size > 0) {
            for (size_t j = 0; j < current_list->size; j++) {
                current_sum += current_list->elements[j];
            }
        }

        if (!has_valid_list || current_sum > max_sum) {
            max_sum = current_sum;
            max_list = current_list;
            has_valid_list = 1;
        }
    }

    return max_list;
}

void cleanup_list_of_lists(ListOfLists *lol) {
    if (lol && lol->lists) {
        for (size_t i = 0; i < lol->count; i++) {
            if (lol->lists[i].elements) {
                free(lol->lists[i].elements);
                lol->lists[i].elements = NULL;
            }
        }
        free(lol->lists);
        lol->lists = NULL;
        lol->count = 0;
    }
}

int main(void) {
    ListOfLists lol = {NULL, 0};
    lol.count = 3;
    lol.lists = (List *)malloc(lol.count * sizeof(List));

    if (!lol.lists) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < lol.count; i++) {
        lol.lists[i].elements = NULL;
        lol.lists[i].size = 0;
    }

    lol.lists[0].size = 3;
    lol.lists[0].elements = (int *)malloc(lol.lists[0].size * sizeof(int));
    if (!lol.lists[0].elements) {
        cleanup_list_of_lists(&lol);
        return EXIT_FAILURE;
    }
    lol.lists[0].elements[0] = 1;
    lol.lists[0].elements[1] = 2;
    lol.lists[0].elements[2] = 3;

    lol.lists[1].size = 2;
    lol.lists[1].elements = (int *)malloc(lol.lists[1].size * sizeof(int));
    if (!lol.lists[1].elements) {
        cleanup_list_of_lists(&lol);
        return EXIT_FAILURE;
    }
    lol.lists[1].elements[0] = 4;
    lol.lists[1].elements[1] = 5;

    lol.lists[2].size = 3;
    lol.lists[2].elements = (int *)malloc(lol.lists[2].size * sizeof(int));
    if (!lol.lists[2].elements) {
        cleanup_list_of_lists(&lol);
        return EXIT_FAILURE;
    }
    lol.lists[2].elements[0] = -1;
    lol.lists[2].elements[1] = 10;
    lol.lists[2].elements[2] = 2;

    const List *max_list = find_max_sum_list(&lol);

    if (max_list && max_list->elements) {
        for (size_t i = 0; i < max_list->size; i++) {
            printf("%d ", max_list->elements[i]);
        }
        printf("\n");
    }

    cleanup_list_of_lists(&lol);

    return EXIT_SUCCESS;
}