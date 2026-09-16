#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    int value;
} Tuple;

int rearrange_tuples(const Tuple *tuples, size_t count,
                     const int *order, size_t order_count,
                     Tuple *result)
{
    size_t i;

    if (tuples == NULL || order == NULL || result == NULL) {
        return -1;
    }
    if (count != order_count) {
        return -1;
    }

    for (i = 0; i < order_count; i++) {
        size_t j;
        size_t found = count;
        for (j = 0; j < count; j++) {
            if (tuples[j].key == order[i]) {
                found = j;
                break;
            }
        }
        if (found == count) {
            return -1;
        }
        result[i] = tuples[found];
    }

    return 0;
}

int main(void)
{
    Tuple tuples[] = { {1, 3}, {2, 4}, {3, 5}, {4, 6} };
    int order[] = { 3, 1, 4, 2 };
    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    size_t order_count = sizeof(order) / sizeof(order[0]);
    Tuple *result;
    size_t i;
    int status;

    result = malloc(count * sizeof(Tuple));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    status = rearrange_tuples(tuples, count, order, order_count, result);
    if (status != 0) {
        fprintf(stderr, "Rearrangement failed\n");
        free(result);
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        if (printf("(%d, %d)\n", result[i].key, result[i].value) < 0) {
            free(result);
            return EXIT_FAILURE;
        }
    }

    free(result);
    return EXIT_SUCCESS;
}