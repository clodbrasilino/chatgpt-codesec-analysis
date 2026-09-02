#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t length;
} tuple_t;

tuple_t *zip_tuples(const tuple_t *t1, const tuple_t *t2) {
    if (t1->length != t2->length) {
        return NULL;
    }

    size_t new_length = t1->length * 2;
    tuple_t *result = (tuple_t *)malloc(sizeof(tuple_t));
    if (!result) {
        return NULL;
    }
    result->data = (int *)malloc(new_length * sizeof(int));
    if (!result->data) {
        free(result);
        return NULL;
    }
    result->length = new_length;

    for (size_t i = 0; i < t1->length; ++i) {
        result->data[i * 2] = t1->data[i];
        result->data[i * 2 + 1] = t2->data[i];
    }

    return result;
}

void free_tuple(tuple_t *t) {
    free(t->data);
    free(t);
}

int main() {
    int arr1[] = {1, 2, 3};
    int arr2[] = {4, 5, 6};

    tuple_t t1 = {arr1, sizeof(arr1) / sizeof(arr1[0])};
    tuple_t t2 = {arr2, sizeof(arr2) / sizeof(arr2[0])};

    tuple_t *zipped = zip_tuples(&t1, &t2);
    if (zipped) {
        for (size_t i = 0; i < zipped->length; ++i) {
            printf("%d ", zipped->data[i]);
        }
        free_tuple(zipped);
    } else {
        fprintf(stderr, "Error: Tuples must have the same length\n");
    }

    return 0;
}