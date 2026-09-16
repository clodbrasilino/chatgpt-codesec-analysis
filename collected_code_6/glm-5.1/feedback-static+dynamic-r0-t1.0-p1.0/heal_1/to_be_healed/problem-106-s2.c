#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

typedef struct {
    Tuple *items;
    size_t count;
} TupleList;

TupleList* add_list_to_tuples(TupleList *tuples, const int *list, size_t list_size) {
    if (tuples == NULL || list == NULL || list_size == 0) {
        return tuples;
    }

    Tuple *new_items = realloc(tuples->items, (tuples->count + list_size) * sizeof(Tuple));
    if (new_items == NULL) {
        return tuples;
    }

    tuples->items = new_items;

    for (size_t i = 0; i < list_size; i++) {
        int *elem = malloc(sizeof(int));
        if (elem == NULL) {
            for (size_t j = tuples->count; j < tuples->count + i; j++) {
                free(tuples->items[j].elements);
            }
            tuples->items = realloc(tuples->items, tuples->count * sizeof(Tuple));
            return tuples;
        }
        *elem = list[i];
        tuples->items[tuples->count + i].elements = elem;
        tuples->items[tuples->count + i].size = 1;
    }

    tuples->count += list_size;
    return tuples;
}

void free_tuples(TupleList *tuples) {
    if (tuples == NULL) {
        return;
    }
    for (size_t i = 0; i < tuples->count; i++) {
        free(tuples->items[i].elements);
    }
    free(tuples->items);
}

int main(void) {
    TupleList tuples = {NULL, 0};
    /* Possible weaknesses found:
     *  Variable 'list' can be declared as const array [constVariable]
     */
    int list[] = {10, 20, 30};

    Tuple t1 = {NULL, 0};
    int e1 = 1;
    t1.elements = &e1;
    t1.size = 1;

    Tuple t2 = {NULL, 0};
    int e2 = 2;
    t2.elements = &e2;
    t2.size = 1;

    tuples.items = malloc(2 * sizeof(Tuple));
    if (tuples.items != NULL) {
        tuples.items[0] = t1;
        tuples.items[1] = t2;
        tuples.count = 2;
    }

    add_list_to_tuples(&tuples, list, 3);

    for (size_t i = 0; i < tuples.count; i++) {
        printf("Tuple %zu: ", i);
        for (size_t j = 0; j < tuples.items[i].size; j++) {
            printf("%d ", tuples.items[i].elements[j]);
        }
        printf("\n");
    }

    for (size_t i = 0; i < tuples.count; i++) {
        if (i >= 2) {
            free(tuples.items[i].elements);
            tuples.items[i].elements = NULL;
        }
    }
    
    free(tuples.items);
    tuples.items = NULL;
    tuples.count = 0;

    return 0;
}