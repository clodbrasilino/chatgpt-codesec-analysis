#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* data;
    size_t len;
} Tuple;

Tuple* create_tuple(size_t len) {
    Tuple *t = (Tuple*)malloc(sizeof(Tuple));
    if (t == NULL) return NULL;
    t->data = (int*)malloc(len * sizeof(int));
    if (t->data == NULL) {
        free(t);
        return NULL;
    }
    t->len = len;
    for (size_t i = 0; i < len; ++i) {
        t->data[i] = i;
    }
    return t;
}

void delete_tuple(Tuple* t) {
    if (t == NULL) return;
    free(t->data);
    free(t);
}

void remove_tuples_of_length_k(Tuple** tuples, size_t* count, size_t k) {
    for (int i = 0; i < *count; ) {
        if (tuples[i]->len == k) {
            delete_tuple(tuples[i]);
            for (int j = i; j < *count - 1; ++j) {
                tuples[j] = tuples[j + 1];
            }
            (*count)--;
        } else {
            i++;
        }
    }
}

int main() {
    Tuple* tuples[10];
    size_t count = 0;

    tuples[count++] = create_tuple(2);
    tuples[count++] = create_tuple(3);
    tuples[count++] = create_tuple(2);
    tuples[count++] = create_tuple(4);
    tuples[count++] = create_tuple(2);

    size_t k = 2;
    remove_tuples_of_length_k(tuples, &count, k);

    for (size_t i = 0; i < count; ++i) {
        for (size_t j = 0; j < tuples[i]->len; ++j) {
            printf("%d ", tuples[i]->data[j]);
        }
        printf("\n");
    }

    for (size_t i = 0; i < count; ++i) {
        delete_tuple(tuples[i]);
    }

    return 0;
}