#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    int size;
} Tuple;

typedef struct {
    Tuple *tuples;
    int count;
} TupleList;

int get_last_element(const Tuple *t) {
    if (t == NULL || t->size == 0 || t->elements == NULL) {
        return 0;
    }
    return t->elements[t->size - 1];
}

int compare_tuples(const void *a, const void *b) {
    const Tuple *tuple_a = (const Tuple *)a;
    const Tuple *tuple_b = (const Tuple *)b;
    int last_a = get_last_element(tuple_a);
    int last_b = get_last_element(tuple_b);
    return last_a - last_b;
}

void sort_tuples_by_last_element(TupleList *list) {
    if (list == NULL || list->tuples == NULL || list->count <= 1) {
        return;
    }
    qsort(list->tuples, list->count, sizeof(Tuple), compare_tuples);
}

void print_tuple_list(const TupleList *list) {
    if (list == NULL) {
        return;
    }
    for (int i = 0; i < list->count; i++) {
        printf("(");
        for (int j = 0; j < list->tuples[i].size; j++) {
            printf("%d", list->tuples[i].elements[j]);
            if (j < list->tuples[i].size - 1) {
                printf(", ");
            }
        }
        printf(")");
        if (i < list->count - 1) {
            printf(", ");
        }
    }
    printf("\n");
}

int main(void) {
    int tuple1_data[] = {2, 1, 5};
    int tuple2_data[] = {3, 4, 1};
    int tuple3_data[] = {1, 2, 3};
    int tuple4_data[] = {5, 6, 2};

    Tuple tuple1 = {tuple1_data, 3};
    Tuple tuple2 = {tuple2_data, 3};
    Tuple tuple3 = {tuple3_data, 3};
    Tuple tuple4 = {tuple4_data, 3};

    Tuple tuples[] = {tuple1, tuple2, tuple3, tuple4};
    TupleList list = {tuples, 4};

    printf("Original list: ");
    print_tuple_list(&list);

    sort_tuples_by_last_element(&list);

    printf("Sorted list:   ");
    print_tuple_list(&list);

    return 0;
}