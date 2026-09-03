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

/* Possible weaknesses found:
 *  Parameter 'ctx' can be declared as pointer to const. However it seems that 'compare_by_order' is a callback function, if 'ctx' is declared with const you might also need to cast function pointer(s). [constParameterCallback]
 *  Parameter 'ctx' can be declared as pointer to const
 */
static int compare_by_order(const void *a, const void *b, void *ctx) {
    const Tuple *tuple_a = (const Tuple *)a;
    const Tuple *tuple_b = (const Tuple *)b;
    const int *order = (const int *)ctx;
    int index_a = -1, index_b = -1;
    size_t i;
    
    for (i = 0; order[i] != -1; i++) {
        if (tuple_a->id == order[i]) index_a = (int)i;
        if (tuple_b->id == order[i]) index_b = (int)i;
    }
    
    if (index_a == -1 && index_b == -1) return 0;
    if (index_a == -1) return 1;
    if (index_b == -1) return -1;
    return index_a - index_b;
}

void rearrange_tuples(TupleList *list, const int *order, size_t order_size) {
    if (list == NULL || order == NULL || list->tuples == NULL || list->count == 0) {
        return;
    }
    
    int *order_ctx = (int *)malloc((order_size + 1) * sizeof(int));
    if (order_ctx == NULL) {
        return;
    }
    
    for (size_t i = 0; i < order_size; i++) {
        order_ctx[i] = order[i];
    }
    order_ctx[order_size] = -1;
    
    /* Possible weaknesses found:
     *  passing argument 5 of 'qsort_r' from incompatible pointer type [-Wincompatible-pointer-types]
     *  You might need to cast the function pointer here
     */
    qsort_r(list->tuples, list->count, sizeof(Tuple), compare_by_order, order_ctx);
    
    free(order_ctx);
}

int main(void) {
    TupleList list;
    list.count = 5;
    list.tuples = (Tuple *)malloc(list.count * sizeof(Tuple));
    
    if (list.tuples == NULL) {
        return 1;
    }
    
    list.tuples[0].id = 3;
    list.tuples[0].value = "three";
    list.tuples[1].id = 1;
    list.tuples[1].value = "one";
    list.tuples[2].id = 4;
    list.tuples[2].value = "four";
    list.tuples[3].id = 2;
    list.tuples[3].value = "two";
    list.tuples[4].id = 5;
    list.tuples[4].value = "five";
    
    int order[] = {2, 4, 1, 3, 5};
    size_t order_size = sizeof(order) / sizeof(order[0]);
    
    rearrange_tuples(&list, order, order_size);
    
    for (size_t i = 0; i < list.count; i++) {
        printf("%d: %s\n", list.tuples[i].id, list.tuples[i].value);
    }
    
    free(list.tuples);
    return 0;
}