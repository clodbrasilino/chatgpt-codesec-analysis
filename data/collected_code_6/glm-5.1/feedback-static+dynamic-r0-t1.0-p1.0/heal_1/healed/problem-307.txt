#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    int *items;
    size_t len;
} Tuple;

Tuple tuple_get_colon(const Tuple *t) {
    Tuple colon = {0};
    if (t == NULL || t->len == 0) {
        return colon;
    }

    size_t total_size = t->len * sizeof(int);
    if (t->len > (size_t)-1 / sizeof(int)) {
        return colon;
    }

    colon.items = (int *)malloc(total_size);
    if (colon.items == NULL) {
        return colon;
    }

    memcpy(colon.items, t->items, total_size);
    colon.len = t->len;
    return colon;
}

void tuple_free(Tuple *t) {
    if (t != NULL) {
        free(t->items);
        t->items = NULL;
        t->len = 0;
    }
}

int main(void) {
    int data[] = {1, 2, 3, 4, 5};
    Tuple original;
    original.items = data;
    original.len = sizeof(data) / sizeof(data[0]);

    Tuple colon = tuple_get_colon(&original);

    if (colon.items != NULL && colon.len > 0) {
        for (size_t i = 0; i < colon.len; i++) {
            printf("%d ", colon.items[i]);
        }
        printf("\n");
    }

    tuple_free(&colon);

    return 0;
}