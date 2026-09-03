#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t length;
} Tuple;

void free_tuple(Tuple *t) {
    if (t->data) {
        free(t->data);
    }
    t->data = NULL;
    t->length = 0;
}

Tuple *create_tuple(size_t length) {
    Tuple *t = (Tuple *)malloc(sizeof(Tuple));
    if (!t) return NULL;
    t->data = (int *)malloc(length * sizeof(int));
    if (!t->data) {
        free(t);
        return NULL;
    }
    t->length = length;
    for (size_t i = 0; i < length; ++i) {
        t->data[i] = i;
    }
    return t;
}

void remove_tuples_with_length_k(Tuple **tuples, size_t *count, size_t k) {
    for (size_t i = 0; i < *count; ) {
        if (tuples[i]->length == k) {
            free_tuple(tuples[i]);
            for (size_t j = i; j < *count - 1; ++j) {
                tuples[j] = tuples[j + 1];
            }
            --(*count);
        } else {
            ++i;
        }
    }
}

int main() {
    size_t count = 5;
    Tuple **tuples = (Tuple **)malloc(count * sizeof(Tuple *));
    if (!tuples) return 1;

    tuples[0] = create_tuple(2);
    tuples[1] = create_tuple(3);
    tuples[2] = create_tuple(2);
    tuples[3] = create_tuple(4);
    tuples[4] = create_tuple(2);

    size_t k = 2;
    remove_tuples_with_length_k(tuples, &count, k);

    for (size_t i = 0; i < count; ++i) {
        for (size_t j = 0; j < tuples[i]->length; ++j) {
            printf("%d ", tuples[i]->data[j]);
        }
        printf("\n");
    }

    for (size_t i = 0; i < count; ++i) {
        free_tuple(tuples[i]);
    }
    free(tuples);

    return 0;
}