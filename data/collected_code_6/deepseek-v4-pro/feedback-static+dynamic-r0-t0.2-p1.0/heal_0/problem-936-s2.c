#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char *value;
} Tuple;

typedef struct {
    int *order;
    int size;
} OrderList;

int find_index(const OrderList *order_list, int id) {
    for (int i = 0; i < order_list->size; i++) {
        if (order_list->order[i] == id) {
            return i;
        }
    }
    return -1;
}

int compare_tuples(const void *a, const void *b, void *arg) {
    const Tuple *tuple_a = (const Tuple *)a;
    const Tuple *tuple_b = (const Tuple *)b;
    const OrderList *order_list = (const OrderList *)arg;
    
    int index_a = find_index(order_list, tuple_a->id);
    int index_b = find_index(order_list, tuple_b->id);
    
    if (index_a == -1 && index_b == -1) return 0;
    if (index_a == -1) return 1;
    if (index_b == -1) return -1;
    
    return index_a - index_b;
}

void rearrange_tuples(Tuple *tuples, int tuple_count, const OrderList *order_list) {
    if (tuples == NULL || order_list == NULL || tuple_count <= 0 || order_list->size <= 0) {
        return;
    }
    
    qsort_r(tuples, tuple_count, sizeof(Tuple), compare_tuples, (void *)order_list);
}

int main(void) {
    Tuple tuples[] = {
        {3, "three"},
        {1, "one"},
        {4, "four"},
        {2, "two"},
        {5, "five"}
    };
    int tuple_count = sizeof(tuples) / sizeof(tuples[0]);
    
    int order_array[] = {2, 4, 1, 3, 5};
    OrderList order_list = {order_array, sizeof(order_array) / sizeof(order_array[0])};
    
    rearrange_tuples(tuples, tuple_count, &order_list);
    
    for (int i = 0; i < tuple_count; i++) {
        printf("(%d, %s) ", tuples[i].id, tuples[i].value);
    }
    printf("\n");
    
    return 0;
}