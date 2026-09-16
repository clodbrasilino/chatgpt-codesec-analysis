#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Tuple;

Tuple* convert_to_ordered_tuples(const int* set, size_t size, size_t* out_size) {
    if (set == NULL || out_size == NULL) {
        return NULL;
    }

    if (size % 2 != 0) {
        return NULL;
    }

    *out_size = size / 2;
    Tuple* tuples = (Tuple*)malloc(*out_size * sizeof(Tuple));
    
    if (tuples == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < *out_size; i++) {
        tuples[i].x = set[2 * i];
        tuples[i].y = set[2 * i + 1];
    }

    return tuples;
}

int main(void) {
    int set[] = {1, 2, 3, 4, 5, 6, 7, 8};
    size_t size = sizeof(set) / sizeof(set[0]);
    size_t tuple_count = 0;

    Tuple* ordered_tuples = convert_to_ordered_tuples(set, size, &tuple_count);

    if (ordered_tuples != NULL) {
        for (size_t i = 0; i < tuple_count; i++) {
            printf("(%d, %d)\n", ordered_tuples[i].x, ordered_tuples[i].y);
        }
        free(ordered_tuples);
    } else {
        fprintf(stderr, "Error converting set to tuples.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}