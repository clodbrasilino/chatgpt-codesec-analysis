#include <stdio.h>
#include <stdlib.h>

typedef struct Tuple {
    int *data;
    int size;
} Tuple;

Tuple* zip(Tuple *t1, Tuple *t2) {
    if (t1 == NULL || t2 == NULL) {
        return NULL;
    }

    if (t1->size != t2->size) {
        return NULL;
    }

    Tuple *result = malloc(sizeof(Tuple));
    if (result == NULL) {
        return NULL;
    }

    result->data = malloc(sizeof(int) * t1->size * 2);
    if (result->data == NULL) {
        free(result);
        return NULL;
    }

    result->size = t1->size * 2;

    for (int i = 0; i < t1->size; ++i) {
        result->data[i*2] = t1->data[i];
        result->data[i*2+1] = t2->data[i];
    }

    return result;
}

int main() {
    Tuple t1 = {(int[]) {1, 2, 3, 4, 5}, 5};
    Tuple t2 = {(int[]) {6, 7, 8, 9, 10}, 5};

    Tuple *result = zip(&t1, &t2);

    if (result == NULL) {
        printf("Can't zip tuples\n");
        return 1;
    }

    for (int i = 0; i < result->size; ++i) {
        printf("%d ", result->data[i]);
    }

    free(result->data);
    free(result);
    return 0;
}