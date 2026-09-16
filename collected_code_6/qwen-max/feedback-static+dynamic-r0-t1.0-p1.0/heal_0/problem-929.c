#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *items;
    size_t size;
} Tuple;

Tuple* create_tuple(size_t size) {
    Tuple *t = (Tuple *)malloc(sizeof(Tuple));
    if (t == NULL) return NULL;
    t->items = (int *)calloc(size, sizeof(int));
    if (t->items == NULL) {
        free(t);
        return NULL;
    }
    t->size = size;
    return t;
}

void free_tuple(Tuple *t) {
    if (t != NULL) {
        free(t->items);
        free(t);
    }
}

int count_repeated_items(Tuple *t) {
    if (t == NULL || t->size == 0) return 0;
    
    int count = 0;
    for (size_t i = 0; i < t->size; ++i) {
        for (size_t j = i + 1; j < t->size; ++j) {
            if (t->items[i] == t->items[j]) {
                count++;
                break;
            }
        }
    }
    return count;
}

int main() {
    Tuple *t = create_tuple(5);
    if (t == NULL) return 1;

    t->items[0] = 1;
    t->items[1] = 2;
    t->items[2] = 1;
    t->items[3] = 3;
    t->items[4] = 2;

    printf("Count of repeated items: %d\n", count_repeated_items(t));

    free_tuple(t);
    return 0;
}