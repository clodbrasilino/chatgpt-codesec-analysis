#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

int tuple_subtract(Tuple a, Tuple b, Tuple *result) {
    if (a.data == NULL || b.data == NULL || result == NULL) {
        return -1;
    }

    if (a.size != b.size) {
        return -1;
    }

    result->data = (int *)malloc(a.size * sizeof(int));
    if (result->data == NULL) {
        return -1;
    }

    result->size = a.size;

    for (size_t i = 0; i < a.size; i++) {
        if ((b.data[i] < 0 && a.data[i] > INT_MAX + b.data[i]) ||
            (b.data[i] > 0 && a.data[i] < INT_MIN + b.data[i])) {
            free(result->data);
            result->data = NULL;
            result->size = 0;
            return -1;
        }
        result->data[i] = a.data[i] - b.data[i];
    }

    return 0;
}

void tuple_free(Tuple *t) {
    if (t != NULL) {
        free(t->data);
        t->data = NULL;
        t->size = 0;
    }
}

int main(void) {
    int d1[] = {10, 20, 30};
    int d2[] = {1, 2, 3};

    Tuple a = {d1, 3};
    Tuple b = {d2, 3};
    Tuple c = {0};

    if (tuple_subtract(a, b, &c) == 0) {
        for (size_t i = 0; i < c.size; i++) {
            printf("%d ", c.data[i]);
        }
        printf("\n");
        tuple_free(&c);
    }

    return 0;
}