#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

typedef struct {
    Tuple *items;
    size_t count;
    size_t capacity;
} TupleList;

int init_list(TupleList *list, size_t capacity) {
    list->items = (Tuple *)malloc(capacity * sizeof(Tuple));
    if (list->items == NULL) {
        return -1;
    }
    list->count = 0;
    list->capacity = capacity;
    return 0;
}

int append_list(TupleList *list, Tuple t) {
    if (list->count == list->capacity) {
        size_t new_capacity = list->capacity * 2;
        Tuple *new_items = (Tuple *)realloc(list->items, new_capacity * sizeof(Tuple));
        if (new_items == NULL) {
            return -1;
        }
        list->items = new_items;
        list->capacity = new_capacity;
    }
    list->items[list->count++] = t;
    return 0;
}

void free_list(TupleList *list) {
    free(list->items);
    list->items = NULL;
    list->count = 0;
    list->capacity = 0;
}

int tuple_equal(Tuple t1, Tuple t2) {
    return t1.a == t2.a && t1.b == t2.b;
}

int find_similar(TupleList *list1, TupleList *list2, TupleList *result) {
    for (size_t i = 0; i < list1->count; i++) {
        for (size_t j = 0; j < list2->count; j++) {
            if (tuple_equal(list1->items[i], list2->items[j])) {
                if (append_list(result, list1->items[i]) != 0) {
                    return -1;
                }
                break;
            }
        }
    }
    return 0;
}

int main(void) {
    TupleList list1, list2, result;

    if (init_list(&list1, 4) != 0) return EXIT_FAILURE;
    if (init_list(&list2, 4) != 0) { free_list(&list1); return EXIT_FAILURE; }
    if (init_list(&result, 4) != 0) { free_list(&list1); free_list(&list2); return EXIT_FAILURE; }

    Tuple t1 = {1, 2};
    Tuple t2 = {3, 4};
    Tuple t3 = {5, 6};
    Tuple t4 = {1, 2};
    Tuple t5 = {7, 8};
    Tuple t6 = {3, 4};

    if (append_list(&list1, t1) != 0) goto cleanup;
    if (append_list(&list1, t2) != 0) goto cleanup;
    if (append_list(&list1, t3) != 0) goto cleanup;

    if (append_list(&list2, t4) != 0) goto cleanup;
    if (append_list(&list2, t5) != 0) goto cleanup;
    if (append_list(&list2, t6) != 0) goto cleanup;

    if (find_similar(&list1, &list2, &result) != 0) goto cleanup;

    for (size_t i = 0; i < result.count; i++) {
        printf("(%d, %d)\n", result.items[i].a, result.items[i].b);
    }

cleanup:
    free_list(&list1);
    free_list(&list2);
    free_list(&result);

    return EXIT_SUCCESS;
}