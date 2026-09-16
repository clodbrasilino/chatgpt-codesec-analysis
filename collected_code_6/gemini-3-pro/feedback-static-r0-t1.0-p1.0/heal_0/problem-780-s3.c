#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Tuple;

typedef struct {
    Tuple* tuples;
    int size;
    int capacity;
} TupleList;

TupleList* create_tuple_list(int capacity) {
    TupleList* list = (TupleList*)malloc(sizeof(TupleList));
    if (!list) {
        return NULL;
    }
    list->tuples = (Tuple*)malloc(capacity * sizeof(Tuple));
    if (!list->tuples) {
        free(list);
        return NULL;
    }
    list->size = 0;
    list->capacity = capacity;
    return list;
}

void add_tuple(TupleList* list, int x, int y) {
    if (!list || list->size >= list->capacity) {
        return;
    }
    list->tuples[list->size].x = x;
    list->tuples[list->size].y = y;
    list->size++;
}

void free_tuple_list(TupleList* list) {
    if (list) {
        free(list->tuples);
        free(list);
    }
}

TupleList* find_sum_combinations(TupleList* list1, TupleList* list2) {
    if (!list1 || !list2) {
        return NULL;
    }

    int result_capacity = list1->size * list2->size;
    TupleList* result = create_tuple_list(result_capacity);
    if (!result) {
        return NULL;
    }

    for (int i = 0; i < list1->size; i++) {
        for (int j = 0; j < list2->size; j++) {
            int sum_x = list1->tuples[i].x + list2->tuples[j].x;
            int sum_y = list1->tuples[i].y + list2->tuples[j].y;
            add_tuple(result, sum_x, sum_y);
        }
    }

    return result;
}

int main() {
    TupleList* list1 = create_tuple_list(2);
    if (!list1) return 1;
    add_tuple(list1, 1, 2);
    add_tuple(list1, 3, 4);

    TupleList* list2 = create_tuple_list(2);
    if (!list2) {
        free_tuple_list(list1);
        return 1;
    }
    add_tuple(list2, 5, 6);
    add_tuple(list2, 7, 8);

    TupleList* result = find_sum_combinations(list1, list2);
    if (!result) {
        free_tuple_list(list1);
        free_tuple_list(list2);
        return 1;
    }

    for (int i = 0; i < result->size; i++) {
        printf("(%d, %d)\n", result->tuples[i].x, result->tuples[i].y);
    }

    free_tuple_list(list1);
    free_tuple_list(list2);
    free_tuple_list(result);

    return 0;
}