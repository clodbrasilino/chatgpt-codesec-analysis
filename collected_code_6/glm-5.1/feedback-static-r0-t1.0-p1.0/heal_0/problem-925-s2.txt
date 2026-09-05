#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

int tuple_product(const Tuple *t, long long *result) {
    if (t == NULL || result == NULL || t->data == NULL) {
        return -1;
    }
    if (t->size == 0) {
        return -1;
    }
    long long product = 1;
    for (size_t i = 0; i < t->size; ++i) {
        product *= t->data[i];
    }
    *result = product;
    return 0;
}

int main(void) {
    int values[] = {2, 3, 4, 5};
    Tuple t;
    t.data = values;
    t.size = sizeof(values) / sizeof(values[0]);

    long long product = 0;
    if (tuple_product(&t, &product) == 0) {
        printf("%lld\n", product);
    } else {
        fprintf(stderr, "Error calculating product\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}