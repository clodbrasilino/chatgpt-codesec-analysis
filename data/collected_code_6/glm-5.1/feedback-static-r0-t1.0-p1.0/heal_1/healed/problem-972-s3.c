#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

typedef struct {
    intptr_t *items;
    size_t len;
} Tuple;

Tuple create_tuple(size_t len) {
    Tuple t;
    t.len = len;
    t.items = (intptr_t *)malloc(len * sizeof(intptr_t));
    if (t.items == NULL) {
        exit(EXIT_FAILURE);
    }
    return t;
}

void free_tuple(Tuple *t) {
    free(t->items);
    t->items = NULL;
    t->len = 0;
}

Tuple concatenate_to_nested(Tuple t1, Tuple t2) {
    Tuple copy1 = create_tuple(t1.len);
    for (size_t i = 0; i < t1.len; i++) {
        copy1.items[i] = t1.items[i];
    }

    Tuple copy2 = create_tuple(t2.len);
    for (size_t i = 0; i < t2.len; i++) {
        copy2.items[i] = t2.items[i];
    }

    Tuple *inner = (Tuple *)malloc(2 * sizeof(Tuple));
    if (inner == NULL) {
        free_tuple(&copy1);
        free_tuple(&copy2);
        exit(EXIT_FAILURE);
    }
    
    inner[0] = copy1;
    inner[1] = copy2;
    
    Tuple nested = create_tuple(2);
    nested.items[0] = (intptr_t)inner;
    nested.items[1] = (intptr_t)sizeof(Tuple);

    return nested;
}

int main(void) {
    Tuple t1 = create_tuple(3);
    t1.items[0] = 1;
    t1.items[1] = 2;
    t1.items[2] = 3;

    Tuple t2 = create_tuple(2);
    t2.items[0] = 4;
    t2.items[1] = 5;

    Tuple nested = concatenate_to_nested(t1, t2);

    Tuple *retrieved = (Tuple *)nested.items[0];

    printf("Nested Tuple:\n");
    printf("Tuple 1: ");
    for (size_t i = 0; i < retrieved[0].len; i++) {
        printf("%ld ", retrieved[0].items[i]);
    }
    printf("\nTuple 2: ");
    for (size_t i = 0; i < retrieved[1].len; i++) {
        printf("%ld ", retrieved[1].items[i]);
    }
    printf("\n");

    free_tuple(&retrieved[0]);
    free_tuple(&retrieved[1]);
    free(retrieved);
    
    free_tuple(&nested);
    free_tuple(&t1);
    free_tuple(&t2);

    return 0;
}