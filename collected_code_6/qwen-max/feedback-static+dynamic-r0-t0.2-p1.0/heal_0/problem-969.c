#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    int value;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t count;
    size_t capacity;
} TupleList;

TupleList* create_tuple_list(size_t initial_capacity) {
    TupleList *list = (TupleList*)malloc(sizeof(TupleList));
    list->tuples = (Tuple*)malloc(initial_capacity * sizeof(Tuple));
    list->count = 0;
    list->capacity = initial_capacity;
    return list;
}

void free_tuple_list(TupleList *list) {
    free(list->tuples);
    free(list);
}

int find_index(TupleList *list, int key) {
    for (size_t i = 0; i < list->count; ++i) {
        if (list->tuples[i].key == key) {
            return i;
        }
    }
    return -1;
}

void add_tuple(TupleList *list, int key, int value) {
    if (list->count >= list->capacity) {
        list->capacity *= 2;
        list->tuples = (Tuple*)realloc(list->tuples, list->capacity * sizeof(Tuple));
    }
    list->tuples[list->count++] = (Tuple){.key = key, .value = value};
}

TupleList* join_tuples(TupleList *list1, TupleList *list2) {
    TupleList *result = create_tuple_list(list1->capacity + list2->capacity);

    for (size_t i = 0; i < list1->count; ++i) {
        add_tuple(result, list1->tuples[i].key, list1->tuples[i].value);
    }

    for (size_t i = 0; i < list2->count; ++i) {
        int index = find_index(result, list2->tuples[i].key);
        if (index != -1) {
            result->tuples[index].value += list2->tuples[i].value;
        } else {
            add_tuple(result, list2->tuples[i].key, list2->tuples[i].value);
        }
    }

    return result;
}

int main() {
    TupleList *list1 = create_tuple_list(3);
    add_tuple(list1, 1, 10);
    add_tuple(list1, 2, 20);
    add_tuple(list1, 3, 30);

    TupleList *list2 = create_tuple_list(3);
    add_tuple(list2, 1, 5);
    add_tuple(list2, 4, 40);
    add_tuple(list2, 5, 50);

    TupleList *result = join_tuples(list1, list2);

    for (size_t i = 0; i < result->count; ++i) {
        printf("(%d, %d)\n", result->tuples[i].key, result->tuples[i].value);
    }

    free_tuple_list(list1);
    free_tuple_list(list2);
    free_tuple_list(result);

    return 0;
}