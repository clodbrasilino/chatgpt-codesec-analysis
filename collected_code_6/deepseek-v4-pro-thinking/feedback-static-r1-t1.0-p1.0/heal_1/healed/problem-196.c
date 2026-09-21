#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *values;
    size_t length;
} tuple_t;

size_t remove_tuples_with_length_k(tuple_t *tuples, size_t count, size_t k) {
    if (tuples == NULL || count == 0) {
        return 0;
    }
    tuple_t *end = tuples + count;
    tuple_t *dst = tuples;
    for (tuple_t *src = tuples; src < end; ++src) {
        if (src->length == k) {
            free(src->values);
            src->values = NULL;
            src->length = 0;
        } else {
            if (dst != src) {
                *dst = *src;
                src->values = NULL;
                src->length = 0;
            }
            ++dst;
        }
    }
    return (size_t)(dst - tuples);
}

static tuple_t create_tuple(size_t length) {
    tuple_t t;
    t.values = NULL;
    t.length = 0;
    if (length > (size_t)-1 / sizeof(*t.values)) {
        return t;
    }
    t.values = malloc(length * sizeof(*t.values));
    if (t.values == NULL && length > 0) {
        t.length = 0;
        return t;
    }
    t.length = length;
    for (size_t i = 0; i < length; ++i) {
        t.values[i] = (int)i;
    }
    return t;
}

static void free_tuples(tuple_t *tuples, size_t count) {
    if (tuples == NULL) {
        return;
    }
    tuple_t *end = tuples + count;
    for (tuple_t *p = tuples; p < end; ++p) {
        free(p->values);
        p->values = NULL;
        p->length = 0;
    }
}

int main(void) {
    const size_t lengths[] = {2, 3, 2, 4, 3};
    size_t count = sizeof(lengths) / sizeof(lengths[0]);
    tuple_t *tuples = malloc(count * sizeof(*tuples));
    if (tuples == NULL) {
        return 1;
    }
    for (size_t i = 0; i < count; ++i) {
        tuples[i] = create_tuple(lengths[i]);
        if (tuples[i].values == NULL && lengths[i] > 0) {
            free_tuples(tuples, i);
            free(tuples);
            return 1;
        }
    }
    size_t new_count = remove_tuples_with_length_k(tuples, count, 2);
    printf("%zu\n", new_count);
    for (size_t i = 0; i < new_count; ++i) {
        printf("%zu ", tuples[i].length);
    }
    printf("\n");
    free_tuples(tuples, new_count);
    free(tuples);
    return 0;
}