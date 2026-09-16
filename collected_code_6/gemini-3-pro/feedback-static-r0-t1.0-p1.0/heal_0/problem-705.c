#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *values;
    size_t length;
} List;

typedef struct {
    List *lists;
    size_t count;
} ListOfLists;

int compare_lists(const void *a, const void *b) {
    const List *list_a = (const List *)a;
    const List *list_b = (const List *)b;

    if (list_a->length != list_b->length) {
        return (list_a->length > list_b->length) - (list_a->length < list_b->length);
    }

    for (size_t i = 0; i < list_a->length; ++i) {
        if (list_a->values[i] != list_b->values[i]) {
            return (list_a->values[i] > list_b->values[i]) - (list_a->values[i] < list_b->values[i]);
        }
    }

    return 0;
}

void sort_list_of_lists(ListOfLists *lol) {
    if (lol == NULL || lol->lists == NULL || lol->count == 0) {
        return;
    }

    qsort(lol->lists, lol->count, sizeof(List), compare_lists);
}

void free_list_of_lists(ListOfLists *lol) {
    if (lol != NULL && lol->lists != NULL) {
        for (size_t i = 0; i < lol->count; ++i) {
            free(lol->lists[i].values);
        }
        free(lol->lists);
        lol->lists = NULL;
        lol->count = 0;
    }
}

int main(void) {
    ListOfLists lol = {0};
    lol.count = 3;
    lol.lists = malloc(lol.count * sizeof(List));

    if (lol.lists == NULL) {
        return EXIT_FAILURE;
    }

    lol.lists[0].length = 3;
    lol.lists[0].values = malloc(3 * sizeof(int));
    if (lol.lists[0].values != NULL) {
        lol.lists[0].values[0] = 3;
        lol.lists[0].values[1] = 2;
        lol.lists[0].values[2] = 1;
    }

    lol.lists[1].length = 2;
    lol.lists[1].values = malloc(2 * sizeof(int));
    if (lol.lists[1].values != NULL) {
        lol.lists[1].values[0] = 4;
        lol.lists[1].values[1] = 5;
    }

    lol.lists[2].length = 3;
    lol.lists[2].values = malloc(3 * sizeof(int));
    if (lol.lists[2].values != NULL) {
        lol.lists[2].values[0] = 1;
        lol.lists[2].values[1] = 2;
        lol.lists[2].values[2] = 3;
    }

    int alloc_failed = 0;
    for (size_t i = 0; i < lol.count; ++i) {
        if (lol.lists[i].values == NULL) {
            alloc_failed = 1;
            break;
        }
    }

    if (alloc_failed) {
        free_list_of_lists(&lol);
        return EXIT_FAILURE;
    }

    sort_list_of_lists(&lol);

    for (size_t i = 0; i < lol.count; ++i) {
        for (size_t j = 0; j < lol.lists[i].length; ++j) {
            printf("%d ", lol.lists[i].values[j]);
        }
        printf("\n");
    }

    free_list_of_lists(&lol);

    return EXIT_SUCCESS;
}