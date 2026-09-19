#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char *value;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t count;
} TupleList;

static int compare_by_order(const void *a, const void *b, void *ctx) {
    const Tuple *tuple_a = (const Tuple *)a;
    const Tuple *tuple_b = (const Tuple *)b;
    const int *order = (const int *)ctx;
    size_t i;
    int index_a = -1, index_b = -1;

    for (i = 0; order[i] != -1; i++) {
        if (tuple_a->id == order[i]) index_a = (int)i;
        if (tuple_b->id == order[i]) index_b = (int)i;
    }

    if (index_a == -1 && index_b == -1) return 0;
    if (index_a == -1) return 1;
    if (index_b == -1) return -1;
    return index_a - index_b;
}

static int *build_order_array(const int *ordered_ids, size_t order_count) {
    int *order = malloc((order_count + 1) * sizeof(int));
    if (!order) return NULL;
    memcpy(order, ordered_ids, order_count * sizeof(int));
    order[order_count] = -1;
    return order;
}

int rearrange_tuples(TupleList *list, const int *ordered_ids, size_t order_count) {
    int *order;
    Tuple *sorted;

    if (!list || !ordered_ids || order_count == 0 || list->count == 0) {
        return -1;
    }

    order = build_order_array(ordered_ids, order_count);
    if (!order) return -1;

    sorted = malloc(list->count * sizeof(Tuple));
    if (!sorted) {
        free(order);
        return -1;
    }

    memcpy(sorted, list->tuples, list->count * sizeof(Tuple));

    qsort_r(sorted, list->count, sizeof(Tuple), compare_by_order, order);

    free(list->tuples);
    list->tuples = sorted;
    free(order);

    return 0;
}

int main(void) {
    TupleList list;
    const int ordered_ids[] = {3, 1, 2};
    size_t i;

    list.count = 4;
    list.tuples = malloc(list.count * sizeof(Tuple));
    if (!list.tuples) return 1;

    list.tuples[0].id = 1;
    list.tuples[0].value = "one";
    list.tuples[1].id = 2;
    list.tuples[1].value = "two";
    list.tuples[2].id = 3;
    list.tuples[2].value = "three";
    list.tuples[3].id = 4;
    list.tuples[3].value = "four";

    if (rearrange_tuples(&list, ordered_ids, 3) != 0) {
        free(list.tuples);
        return 1;
    }

    for (i = 0; i < list.count; i++) {
        printf("%d: %s\n", list.tuples[i].id, list.tuples[i].value);
    }

    free(list.tuples);
    return 0;
}