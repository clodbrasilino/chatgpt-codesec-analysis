#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    int value;
} Tuple;

int rearrange_tuples(Tuple *tuples, size_t tuple_count, const size_t *order, size_t order_count) {
    if (tuples == NULL || order == NULL) {
        return -1;
    }
    if (tuple_count == 0 || order_count != tuple_count) {
        return -2;
    }

    Tuple *temp = malloc(tuple_count * sizeof(*temp));
    if (temp == NULL) {
        return -3;
    }

    memcpy(temp, tuples, tuple_count * sizeof(*temp));

    for (size_t i = 0; i < order_count; ++i) {
        if (order[i] >= tuple_count) {
            free(temp);
            return -4;
        }
        tuples[i] = temp[order[i]];
    }

    free(temp);
    return 0;
}

int main(void) {
    Tuple tuples[] = {
        {1, 100},
        {2, 200},
        {3, 300},
        {4, 400}
    };
    size_t order[] = {2, 0, 3, 1};
    size_t count = sizeof(tuples) / sizeof(tuples[0]);

    if (rearrange_tuples(tuples, count, order, count) != 0) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        printf("(%d, %d)\n", tuples[i].id, tuples[i].value);
    }

    return EXIT_SUCCESS;
}