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
    const int list[] = {10, 20, 30};
    int e1 = 1;
    int e2 = 2;
    
    tuples.items = malloc(2 * sizeof(Tuple));
    if (tuples.items != NULL) {
        tuples.items[0].elements = &e1;
        tuples.items[0].size = 1;
        tuples.items[1].elements = &e2;
        tuples.items[1].size = 1;
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

    free_tuples(&tuples);

    return 0;
}