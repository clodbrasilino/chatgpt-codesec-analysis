#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t len;
} Tuple;

void addListToTuples(Tuple *t, const int *list, size_t list_len) {
    if (t == NULL || t->data == NULL || list == NULL) return;
    size_t new_len = t->len + list_len;
    t->data = realloc(t->data, new_len * sizeof(int));
    if (t->data == NULL) return;
    for (size_t i = 0; i < list_len; ++i) {
        t->data[t->len + i] = list[i];
    }
    t->len = new_len;
}

int main() {
    Tuple t;
    t.data = (int *)malloc(10 * sizeof(int));
    t.len = 4;
    t.data[0] = 1;
    t.data[1] = 2;
    t.data[2] = 3;
    t.data[3] = 4;

    /* Possible weaknesses found:
     *  Variable 'list' can be declared as const array [constVariable]
     */
    int list[] = {5, 6, 7, 8};
    size_t list_len = 4;

    addListToTuples(&t, list, list_len);

    for (size_t i = 0; i < t.len; ++i) {
        printf("%d ", t.data[i]);
    }

    free(t.data);
    return 0;
}