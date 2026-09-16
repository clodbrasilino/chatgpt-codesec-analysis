#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *items;
    int count;
    int capacity;
} Tuple;

typedef struct {
    int *items;
    int count;
} List;

int tuple_init(Tuple *t, int capacity) {
    t->items = (int *)malloc(capacity * sizeof(int));
    if (!t->items) {
        return -1;
    }
    t->capacity = capacity;
    t->count = 0;
    return 0;
}

void tuple_free(Tuple *t) {
    free(t->items);
    t->items = NULL;
    t->capacity = 0;
    t->count = 0;
}

int tuple_add(Tuple *t, int value) {
    if (t->count >= t->capacity) {
        int new_capacity = t->capacity == 0 ? 4 : t->capacity * 2;
        int *new_items = (int *)realloc(t->items, new_capacity * sizeof(int));
        if (!new_items) {
            return -1;
        }
        t->items = new_items;
        t->capacity = new_capacity;
    }
    t->items[t->count] = value;
    t->count++;
    return 0;
}

int add_list_to_tuples(Tuple *tuples, int tuple_count, List *list) {
    if (!tuples || !list) {
        return -1;
    }
    for (int i = 0; i < tuple_count; i++) {
        for (int j = 0; j < list->count; j++) {
            if (tuple_add(&tuples[i], list->items[j]) != 0) {
                return -1;
            }
        }
    }
    return 0;
}

int main() {
    Tuple tuples[2];
    for (int i = 0; i < 2; i++) {
        if (tuple_init(&tuples[i], 2) != 0) {
            for (int k = 0; k < i; k++) {
                tuple_free(&tuples[k]);
            }
            return 1;
        }
    }

    if (tuple_add(&tuples[0], 1) != 0 || tuple_add(&tuples[0], 2) != 0) {
        tuple_free(&tuples[0]);
        tuple_free(&tuples[1]);
        return 1;
    }
    if (tuple_add(&tuples[1], 3) != 0 || tuple_add(&tuples[1], 4) != 0) {
        tuple_free(&tuples[0]);
        tuple_free(&tuples[1]);
        return 1;
    }

    List list;
    int list_items[] = {10, 20};
    list.items = list_items;
    list.count = 2;

    if (add_list_to_tuples(tuples, 2, &list) != 0) {
        tuple_free(&tuples[0]);
        tuple_free(&tuples[1]);
        return 1;
    }

    for (int i = 0; i < 2; i++) {
        printf("Tuple %d: ", i);
        for (int j = 0; j < tuples[i].count; j++) {
            printf("%d ", tuples[i].items[j]);
        }
        printf("\n");
        tuple_free(&tuples[i]);
    }

    return 0;
}