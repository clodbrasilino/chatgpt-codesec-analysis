#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *array;
    size_t size;
} InnerList;

typedef struct {
    InnerList *lists;
    size_t count;
} ListOfLists;

typedef struct {
    size_t index;
} SortContext;

static SortContext sort_context;

int compare_inner_lists(const void *a, const void *b) {
    const InnerList *list_a = (const InnerList *)a;
    const InnerList *list_b = (const InnerList *)b;

    if (sort_context.index >= list_a->size || sort_context.index >= list_b->size) {
        return 0;
    }

    int val_a = list_a->array[sort_context.index];
    int val_b = list_b->array[sort_context.index];

    if (val_a < val_b) return -1;
    if (val_a > val_b) return 1;
    return 0;
}

void sort_list_of_lists(ListOfLists *lol, size_t index) {
    if (!lol || !lol->lists || lol->count == 0) {
        return;
    }

    sort_context.index = index;
    qsort(lol->lists, lol->count, sizeof(InnerList), compare_inner_lists);
}

int main(void) {
    ListOfLists lol;
    lol.count = 3;
    lol.lists = calloc(lol.count, sizeof(InnerList));
    
    if (!lol.lists) {
        return 1;
    }

    for (size_t i = 0; i < lol.count; ++i) {
        lol.lists[i].size = 3;
        lol.lists[i].array = calloc(lol.lists[i].size, sizeof(int));
        if (!lol.lists[i].array) {
            for (size_t j = 0; j < i; ++j) {
                free(lol.lists[j].array);
            }
            free(lol.lists);
            return 1;
        }
    }

    lol.lists[0].array[0] = 5; lol.lists[0].array[1] = 9; lol.lists[0].array[2] = 2;
    lol.lists[1].array[0] = 3; lol.lists[1].array[1] = 1; lol.lists[1].array[2] = 8;
    lol.lists[2].array[0] = 4; lol.lists[2].array[1] = 6; lol.lists[2].array[2] = 1;

    sort_list_of_lists(&lol, 1);

    for (size_t i = 0; i < lol.count; ++i) {
        for (size_t j = 0; j < lol.lists[i].size; ++j) {
            printf("%d ", lol.lists[i].array[j]);
        }
        printf("\n");
    }

    for (size_t i = 0; i < lol.count; ++i) {
        free(lol.lists[i].array);
    }
    free(lol.lists);

    return 0;
}