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
    tuple_t *write_ptr = tuples;
    tuple_t *read_ptr = tuples;
    tuple_t *end = tuples + count;
    while (read_ptr < end) {
        if (read_ptr->length == k) {
            free(read_ptr->values);
            read_ptr->values = NULL;
            read_ptr->length = 0;
        } else {
            if (write_ptr != read_ptr) {
                *write_ptr = *read_ptr;
                read_ptr->values = NULL;
                read_ptr->length = 0;
            }
            ++write_ptr;
        }
        ++read_ptr;
    }
    return (size_t)(write_ptr - tuples);
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
    size_t i;
    for (i = 0; i < length; ++i) {
        t.values[i] = (int)i;
    }
    return t;
}

static void free_tuples(tuple_t *tuples, size_t count) {
    if (tuples == NULL) {
        return;
    }
    size_t i;
    for (i = 0; i < count; ++i) {
        free(tuples[i].values);
        tuples[i].values = NULL;
        tuples[i].length = 0;
    }
}

int main(void) {
    size_t count = 5;
    static const size_t lengths[] = {2, 3, 2, 4, 3};
    size_t i;
    tuple_t *tuples = malloc(count * sizeof(*tuples));
    if (tuples == NULL) {
        return 1;
    }
    for (i = 0; i < count; ++i) {
        tuples[i] = create_tuple(lengths[i]);
        if (tuples[i].values == NULL && lengths[i] > 0) {
            free_tuples(tuples, i);
            free(tuples);
            return 1;
        }
    }
    size_t new_count = remove_tuples_with_length_k(tuples, count, 2);
    printf("%zu\n", new_count);
    for (i = 0; i < new_count; ++i) {
        printf("%zu ", tuples[i].length);
    }
    printf("\n");
    free_tuples(tuples, new_count);
    free(tuples);
    return 0;
}