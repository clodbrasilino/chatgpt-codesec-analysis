#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    Tuple *data;
    size_t size;
    size_t capacity;
} TupleList;

int tuple_equals(Tuple a, Tuple b) {
    return a.first == b.first && a.second == b.second;
}

void tuple_list_init(TupleList *list) {
    list->data = NULL;
    list->size = 0;
    list->capacity = 0;
}

int tuple_list_push(TupleList *list, Tuple t) {
    if (list->size == list->capacity) {
        size_t new_capacity = list->capacity == 0 ? 8 : list->capacity * 2;
        Tuple *new_data = realloc(list->data, new_capacity * sizeof(Tuple));
        if (new_data == NULL) {
            return 0;
        }
        list->data = new_data;
        list->capacity = new_capacity;
    }
    list->data[list->size++] = t;
    return 1;
}

void tuple_list_free(TupleList *list) {
    free(list->data);
    list->data = NULL;
    list->size = 0;
    list->capacity = 0;
}

int tuple_list_contains(TupleList *list, Tuple t) {
    for (size_t i = 0; i < list->size; i++) {
        if (tuple_equals(list->data[i], t)) {
            return 1;
        }
    }
    return 0;
}

TupleList remove_matching_tuples(TupleList *list1, TupleList *list2) {
    TupleList result;
    tuple_list_init(&result);

    for (size_t i = 0; i < list1->size; i++) {
        if (!tuple_list_contains(list2, list1->data[i])) {
            if (!tuple_list_push(&result, list1->data[i])) {
                tuple_list_free(&result);
                tuple_list_init(&result);
                return result;
            }
        }
    }

    for (size_t i = 0; i < list2->size; i++) {
        if (!tuple_list_contains(list1, list2->data[i])) {
            if (!tuple_list_push(&result, list2->data[i])) {
                tuple_list_free(&result);
                tuple_list_init(&result);
                return result;
            }
        }
    }

    return result;
}

void print_tuple_list(TupleList *list) {
    printf("[");
    for (size_t i = 0; i < list->size; i++) {
        printf("(%d, %d)", list->data[i].first, list->data[i].second);
        if (i < list->size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main(void) {
    TupleList list1, list2;
    tuple_list_init(&list1);
    tuple_list_init(&list2);

    Tuple t1 = {1, 2};
    Tuple t2 = {3, 4};
    Tuple t3 = {5, 6};
    Tuple t4 = {1, 2};
    Tuple t5 = {7, 8};

    tuple_list_push(&list1, t1);
    tuple_list_push(&list1, t2);
    tuple_list_push(&list1, t3);

    tuple_list_push(&list2, t4);
    tuple_list_push(&list2, t5);
    tuple_list_push(&list2, t2);

    printf("List 1: ");
    print_tuple_list(&list1);
    printf("List 2: ");
    print_tuple_list(&list2);

    TupleList result = remove_matching_tuples(&list1, &list2);

    printf("Result: ");
    print_tuple_list(&result);

    tuple_list_free(&list1);
    tuple_list_free(&list2);
    tuple_list_free(&result);

    return 0;
}