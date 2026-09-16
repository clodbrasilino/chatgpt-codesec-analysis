#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t length;
} Tuple;

Tuple* create_tuple(size_t length) {
    Tuple *tuple = (Tuple*)malloc(sizeof(Tuple));
    if (!tuple) return NULL;
    tuple->data = (int*)malloc(length * sizeof(int));
    if (!tuple->data) {
        free(tuple);
        return NULL;
    }
    tuple->length = length;
    return tuple;
}

void destroy_tuple(Tuple *tuple) {
    if (tuple) {
        free(tuple->data);
        free(tuple);
    }
}

Tuple* concatenate_tuples(const Tuple *t1, const Tuple *t2) {
    Tuple *result = create_tuple(t1->length + t2->length);
    if (!result) return NULL;
    for (size_t i = 0; i < t1->length; ++i) {
        result->data[i] = t1->data[i];
    }
    for (size_t i = 0; i < t2->length; ++i) {
        result->data[t1->length + i] = t2->data[i];
    }
    return result;
}

int main() {
    Tuple *t1 = create_tuple(3);
    if (t1) {
        t1->data[0] = 1;
        t1->data[1] = 2;
        t1->data[2] = 3;
    }

    Tuple *t2 = create_tuple(4);
    if (t2) {
        t2->data[0] = 4;
        t2->data[1] = 5;
        t2->data[2] = 6;
        t2->data[3] = 7;
    }

    Tuple *result = concatenate_tuples(t1, t2);
    if (result) {
        for (size_t i = 0; i < result->length; ++i) {
            printf("%d ", result->data[i]);
        }
        printf("\n");
        destroy_tuple(result);
    }

    destroy_tuple(t1);
    destroy_tuple(t2);

    return 0;
}