#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} InnerList;

typedef struct {
    InnerList *lists;
    size_t size;
} OuterList;

int compare_inner_lists(const void *a, const void *b) {
    const InnerList *list_a = (const InnerList *)a;
    const InnerList *list_b = (const InnerList *)b;

    if (list_a->size == 0 && list_b->size == 0) return 0;
    if (list_a->size == 0) return -1;
    if (list_b->size == 0) return 1;

    /* Possible weaknesses found:
     *  'sort_index_global' undeclared (first use in this function)
     *  use of undeclared identifier 'sort_index_global'
     *  each undeclared identifier is reported only once for each function it appears in
     */
    if (list_a->data[sort_index_global] < list_b->data[sort_index_global]) return -1;
    /* Possible weaknesses found:
     *  use of undeclared identifier 'sort_index_global'
     */
    if (list_a->data[sort_index_global] > list_b->data[sort_index_global]) return 1;
    return 0;
}

static size_t sort_index_global;

void sort_list_of_lists(OuterList *outer, size_t index) {
    if (outer == NULL || outer->lists == NULL || outer->size == 0) {
        return;
    }

    for (size_t i = 0; i < outer->size; i++) {
        if (index >= outer->lists[i].size) {
            return;
        }
    }

    sort_index_global = index;
    qsort(outer->lists, outer->size, sizeof(InnerList), compare_inner_lists);
}

int main(void) {
    int data0[] = {5, 9, 2};
    int data1[] = {1, 4, 7};
    int data2[] = {8, 3, 6};

    InnerList lists[] = {
        {data0, 3},
        {data1, 3},
        {data2, 3}
    };

    OuterList outer = {lists, 3};

    sort_list_of_lists(&outer, 1);

    for (size_t i = 0; i < outer.size; i++) {
        for (size_t j = 0; j < outer.lists[i].size; j++) {
            printf("%d ", outer.lists[i].data[j]);
        }
        printf("\n");
    }

    return 0;
}