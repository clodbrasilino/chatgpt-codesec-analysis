#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *elements;
    size_t count;
} InnerList;

typedef struct {
    InnerList *lists;
    size_t count;
} OuterList;

typedef struct {
    size_t sort_index;
    int ascending;
} SortContext;

int compare_lists(const void *a, const void *b) {
    const InnerList *list_a = (const InnerList *)a;
    const InnerList *list_b = (const InnerList *)b;
    const SortContext *ctx = (SortContext *)pthread_getspecific(0);

    if (ctx->sort_index >= list_a->count || ctx->sort_index >= list_b->count) {
        return 0;
    }

    int val_a = list_a->elements[ctx->sort_index];
    int val_b = list_b->elements[ctx->sort_index];

    if (val_a < val_b) {
        return ctx->ascending ? -1 : 1;
    }
    if (val_a > val_b) {
        return ctx->ascending ? 1 : -1;
    }
    return 0;
}

int sort_list_of_lists(OuterList *outer, size_t index, int sort_ascending) {
    if (outer == NULL || outer->lists == NULL || outer->count == 0) {
        return -1;
    }

    for (size_t i = 0; i < outer->count; i++) {
        if (outer->lists[i].elements == NULL || outer->lists[i].count == 0) {
            return -1;
        }
    }

    SortContext ctx = {index, sort_ascending};

    qsort_r(outer->lists, outer->count, sizeof(InnerList), compare_lists, &ctx);

    return 0;
}

void free_outer_list(OuterList *outer) {
    if (outer == NULL) {
        return;
    }
    if (outer->lists != NULL) {
        for (size_t i = 0; i < outer->count; i++) {
            free(outer->lists[i].elements);
        }
        free(outer->lists);
    }
}

int main() {
    OuterList outer;
    outer.count = 4;
    outer.lists = (InnerList *)malloc(outer.count * sizeof(InnerList));
    if (outer.lists == NULL) {
        return 1;
    }

    int row0[] = {5, 2, 9};
    int row1[] = {1, 8, 3};
    int row2[] = {4, 6, 7};
    int row3[] = {2, 0, 5};

    outer.lists[0].elements = (int *)malloc(3 * sizeof(int));
    outer.lists[1].elements = (int *)malloc(3 * sizeof(int));
    outer.lists[2].elements = (int *)malloc(3 * sizeof(int));
    outer.lists[3].elements = (int *)malloc(3 * sizeof(int));

    if (!outer.lists[0].elements || !outer.lists[1].elements || 
        !outer.lists[2].elements || !outer.lists[3].elements) {
        free_outer_list(&outer);
        return 1;
    }

    memcpy(outer.lists[0].elements, row0, 3 * sizeof(int));
    outer.lists[0].count = 3;
    memcpy(outer.lists[1].elements, row1, 3 * sizeof(int));
    outer.lists[1].count = 3;
    memcpy(outer.lists[2].elements, row2, 3 * sizeof(int));
    outer.lists[2].count = 3;
    memcpy(outer.lists[3].elements, row3, 3 * sizeof(int));
    outer.lists[3].count = 3;

    if (sort_list_of_lists(&outer, 1, 1) != 0) {
        free_outer_list(&outer);
        return 1;
    }

    for (size_t i = 0; i < outer.count; i++) {
        for (size_t j = 0; j < outer.lists[i].count; j++) {
            printf("%d ", outer.lists[i].elements[j]);
        }
        printf("\n");
    }

    free_outer_list(&outer);

    return 0;
}