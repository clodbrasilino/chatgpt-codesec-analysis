#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int length;
} Tuple;

void free_tuple(Tuple *t) {
    free(t->data);
}

int tuple_length(Tuple *t) {
    return t->length;
}

void remove_tuples_of_length_k(Tuple *t, int k) {
    if (t == NULL || t->data == NULL) {
        return;
    }

    int *new_data = malloc((t->length - k) * sizeof(int));
    if (new_data == NULL) {
        free_tuple(t);
        return;
    }

    int new_length = 0;
    for (int i = 0; i < t->length; i++) {
        if (i < k || i >= t->length - k) {
            new_data[new_length++] = t->data[i];
        }
    }

    free(t->data);
    t->data = new_data;
    t->length = new_length;
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