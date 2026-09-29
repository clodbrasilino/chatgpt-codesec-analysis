#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

Tuple* tuple_subtract(const Tuple *t1, const Tuple *t2) {
    if (t1 == NULL || t2 == NULL) {
        return NULL;
    }

    if (t1->size != t2->size) {
        return NULL;
    }

    Tuple *result = (Tuple *)malloc(sizeof(Tuple));
    if (result == NULL) {
        return NULL;
    }

    result->size = t1->size;
    result->data = (int *)malloc(result->size * sizeof(int));
    if (result->data == NULL) {
        free(result);
        return NULL;
    }

    for (size_t i = 0; i < result->size; i++) {
        result->data[i] = t1->data[i] - t2->data[i];
    }

    return result;
}

void tuple_free(Tuple *t) {
    if (t != NULL) {
        free(t->data);
        free(t);
    }
}

int main(void) {
    int a[] = {10, 20, 30, 40};
    int b[] = {1, 2, 3, 4};

    Tuple t1 = {a, 4};
    Tuple t2 = {b, 4};

    Tuple *res = tuple_subtract(&t1, &t2);
    if (res == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < res->size; i++) {
        printf("%d ", res->data[i]);
    }
    printf("\n");

    tuple_free(res);

    return EXIT_SUCCESS;
}