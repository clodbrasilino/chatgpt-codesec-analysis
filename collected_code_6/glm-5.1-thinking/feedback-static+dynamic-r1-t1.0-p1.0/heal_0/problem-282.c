#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} IntList;

IntList subtract_lists(const IntList *a, const IntList *b) {
    IntList result;
    result.size = 0;
    result.data = NULL;

    if (a == NULL || b == NULL) {
        return result;
    }

    if (a->data == NULL || b->data == NULL) {
        return result;
    }

    if (a->size != b->size) {
        return result;
    }

    if (a->size == 0) {
        return result;
    }

    result.data = malloc(a->size * sizeof(int));
    if (result.data == NULL) {
        return result;
    }

    result.size = a->size;

    for (size_t i = 0; i < a->size; ++i) {
        result.data[i] = a->data[i] - b->data[i];
    }

    return result;
}

int main(void) {
    IntList a;
    IntList b;

    a.size = 5;
    b.size = 5;

    a.data = malloc(a.size * sizeof(int));
    if (a.data == NULL) {
        return EXIT_FAILURE;
    }

    b.data = malloc(b.size * sizeof(int));
    if (b.data == NULL) {
        free(a.data);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < a.size; ++i) {
        a.data[i] = (int)(i * 10);
        b.data[i] = (int)i;
    }

    IntList c = subtract_lists(&a, &b);

    if (c.data != NULL) {
        for (size_t i = 0; i < c.size; ++i) {
            printf("%d ", c.data[i]);
        }
        printf("\n");
        free(c.data);
    }

    free(a.data);
    free(b.data);

    return EXIT_SUCCESS;
}