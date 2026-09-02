#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t length;
} Tuple;

Tuple create_tuple(size_t size) {
    Tuple t = {NULL, 0};
    t.data = (int*)malloc(size * sizeof(int));
    if (t.data != NULL) {
        t.length = size;
    }
    return t;
}

void free_tuple(Tuple *t) {
    if (t->data != NULL) {
        free(t->data);
        t->data = NULL;
        t->length = 0;
    }
}

size_t find_dissimilar_elements(const Tuple *tuple1, const Tuple *tuple2, Tuple *result) {
    size_t count = 0;
    for (size_t i = 0; i < tuple1->length && i < tuple2->length; ++i) {
        if (tuple1->data[i] != tuple2->data[i]) {
            result->data[count++] = tuple1->data[i];
        }
    }
    for (size_t i = tuple2->length; i < tuple1->length; ++i) {
        result->data[count++] = tuple1->data[i];
    }
    result->length = count;
    return count;
}

int main() {
    Tuple tuple1 = create_tuple(5);
    Tuple tuple2 = create_tuple(5);
    Tuple result = create_tuple(10);

    if (tuple1.data == NULL || tuple2.data == NULL || result.data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free_tuple(&tuple1);
        free_tuple(&tuple2);
        free_tuple(&result);
        return 1;
    }

    tuple1.data[0] = 1; tuple1.data[1] = 2; tuple1.data[2] = 3; tuple1.data[3] = 4; tuple1.data[4] = 5;
    tuple2.data[0] = 1; tuple2.data[1] = 2; tuple2.data[2] = 6; tuple2.data[3] = 8; tuple2.data[4] = 5;

    size_t dissimilar_count = find_dissimilar_elements(&tuple1, &tuple2, &result);

    for (size_t i = 0; i < dissimilar_count; ++i) {
        printf("%d ", result.data[i]);
    }
    printf("\n");

    free_tuple(&tuple1);
    free_tuple(&tuple2);
    free_tuple(&result);

    return 0;
}