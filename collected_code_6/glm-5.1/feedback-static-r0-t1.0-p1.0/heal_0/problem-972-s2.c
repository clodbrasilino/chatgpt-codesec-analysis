#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *items;
    size_t len;
} Tuple;

typedef struct {
    Tuple t1;
    Tuple t2;
} NestedTuple;

Tuple create_tuple(size_t len) {
    Tuple t;
    t.len = len;
    if (len > 0) {
        t.items = (int *)malloc(len * sizeof(int));
        if (t.items == NULL) {
            exit(EXIT_FAILURE);
        }
    } else {
        t.items = NULL;
    }
    return t;
}

void free_tuple(Tuple *t) {
    if (t != NULL) {
        free(t->items);
        t->items = NULL;
        t->len = 0;
    }
}

NestedTuple concatenate_to_nested(Tuple a, Tuple b) {
    NestedTuple nt;
    
    nt.t1 = create_tuple(a.len);
    if (a.len > 0) {
        memcpy(nt.t1.items, a.items, a.len * sizeof(int));
    }
    
    nt.t2 = create_tuple(b.len);
    if (b.len > 0) {
        memcpy(nt.t2.items, b.items, b.len * sizeof(int));
    }
    
    return nt;
}

int main(void) {
    Tuple t1 = create_tuple(3);
    t1.items[0] = 1;
    t1.items[1] = 2;
    t1.items[2] = 3;

    Tuple t2 = create_tuple(2);
    t2.items[0] = 4;
    t2.items[1] = 5;

    NestedTuple nt = concatenate_to_nested(t1, t2);

    printf("Nested Tuple: (");
    printf("(");
    for (size_t i = 0; i < nt.t1.len; i++) {
        printf("%d", nt.t1.items[i]);
        if (i < nt.t1.len - 1) printf(", ");
    }
    printf("), (");
    for (size_t i = 0; i < nt.t2.len; i++) {
        printf("%d", nt.t2.items[i]);
        if (i < nt.t2.len - 1) printf(", ");
    }
    printf("))\n");

    free_tuple(&t1);
    free_tuple(&t2);
    free_tuple(&nt.t1);
    free_tuple(&nt.t2);

    return 0;
}