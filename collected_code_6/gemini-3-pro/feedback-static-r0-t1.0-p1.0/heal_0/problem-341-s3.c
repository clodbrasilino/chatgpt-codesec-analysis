#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    int first;
    int second;
} Tuple;

Tuple* generate_ordered_tuples(const int* set, size_t set_size, size_t* out_count) {
    if (!set || !out_count) {
        return NULL;
    }

    size_t count = set_size * set_size;
    *out_count = count;

    if (count == 0) {
        return NULL;
    }

    Tuple* tuples = (Tuple*)malloc(count * sizeof(Tuple));
    if (!tuples) {
        *out_count = 0;
        return NULL;
    }

    size_t index = 0;
    for (size_t i = 0; i < set_size; ++i) {
        for (size_t j = 0; j < set_size; ++j) {
            tuples[index].first = set[i];
            tuples[index].second = set[j];
            ++index;
        }
    }

    return tuples;
}

int main(void) {
    int my_set[] = {1, 2, 3};
    size_t set_size = sizeof(my_set) / sizeof(my_set[0]);
    size_t tuple_count = 0;

    Tuple* my_tuples = generate_ordered_tuples(my_set, set_size, &tuple_count);

    if (my_tuples) {
        for (size_t i = 0; i < tuple_count; ++i) {
            printf("(%d, %d)\n", my_tuples[i].first, my_tuples[i].second);
        }
        free(my_tuples);
    }

    return 0;
}