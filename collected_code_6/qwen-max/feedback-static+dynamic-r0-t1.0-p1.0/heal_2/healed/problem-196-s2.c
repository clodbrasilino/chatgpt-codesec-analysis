#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int length;
} Tuple;

void free_tuple(Tuple *t) {
    free(t->data);
}

int tuple_length(const Tuple *t) {
    return t->length;
}

void remove_tuples_of_length_k(Tuple *t, int k) {
    if (t == NULL || t->data == NULL) {
        return;
    }

    const int new_length = t->length - k;
    if (new_length <= 0) {
        free_tuple(t);
        t->data = NULL;
        t->length = 0;
        return;
    }

    int *new_data = malloc(new_length * sizeof(int));
    if (new_data == NULL) {
        free_tuple(t);
        return;
    }

    int j = 0;
    for (int i = 0; i < t->length; i++) {
        if (i >= k) {
            new_data[j++] = t->data[i];
        }
        if (j >= new_length) break;
    }

    free(t->data);
    t->data = new_data;
    t->length = j;
}

int main() {
    Tuple t = { .data = malloc(10 * sizeof(int)), .length = 10 };
    for (int i = 0; i < t.length; i++) {
        t.data[i] = i;
    }

    int k = 3;
    remove_tuples_of_length_k(&t, k);

    for (int i = 0; i < t.length; i++) {
        printf("%d ", t.data[i]);
    }
    printf("\n");

    free_tuple(&t);
    return 0;
}