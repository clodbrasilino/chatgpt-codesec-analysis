#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} InnerList;

typedef struct {
    InnerList *lists;
    size_t count;
} ListOfLists;

static size_t sort_index = 0;

int compare_inner_lists(const void *a, const void *b) {
    const InnerList *list_a = (const InnerList *)a;
    const InnerList *list_b = (const InnerList *)b;

    if (sort_index >= list_a->size || sort_index >= list_b->size) {
        return 0;
    }

    int val_a = list_a->data[sort_index];
    int val_b = list_b->data[sort_index];

    if (val_a < val_b) return -1;
    if (val_a > val_b) return 1;
    return 0;
}

int sort_list_of_lists(ListOfLists *lol, size_t index) {
    if (!lol || !lol->lists || lol->count == 0) {
        return -1;
    }

    for (size_t i = 0; i < lol->count; i++) {
        if (!lol->lists[i].data || index >= lol->lists[i].size) {
            return -1;
        }
    }

    sort_index = index;
    qsort(lol->lists, lol->count, sizeof(InnerList), compare_inner_lists);

    return 0;
}

void free_list_of_lists(ListOfLists *lol) {
    if (!lol) return;
    if (lol->lists) {
        for (size_t i = 0; i < lol->count; i++) {
            free(lol->lists[i].data);
        }
        free(lol->lists);
    }
}

int main(void) {
    ListOfLists lol;
    lol.count = 3;
    lol.lists = malloc(lol.count * sizeof(InnerList));
    if (!lol.lists) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < lol.count; i++) {
        lol.lists[i].size = 3;
        lol.lists[i].data = malloc(lol.lists[i].size * sizeof(int));
        if (!lol.lists[i].data) {
            lol.count = i;
            free_list_of_lists(&lol);
            return EXIT_FAILURE;
        }
    }

    lol.lists[0].data[0] = 3; lol.lists[0].data[1] = 10; lol.lists[0].data[2] = 5;
    lol.lists[1].data[0] = 1; lol.lists[1].data[1] = 20; lol.lists[1].data[2] = 4;
    lol.lists[2].data[0] = 2; lol.lists[2].data[1] = 5;  lol.lists[2].data[2] = 6;

    if (sort_list_of_lists(&lol, 1) != 0) {
        free_list_of_lists(&lol);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < lol.count; i++) {
        for (size_t j = 0; j < lol.lists[i].size; j++) {
            printf("%d ", lol.lists[i].data[j]);
        }
        printf("\n");
    }

    free_list_of_lists(&lol);
    return EXIT_SUCCESS;
}