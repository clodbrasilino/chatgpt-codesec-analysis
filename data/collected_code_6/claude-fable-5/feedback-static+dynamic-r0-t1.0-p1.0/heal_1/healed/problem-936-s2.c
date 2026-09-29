#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    int value;
} Tuple;

int rearrange_tuples(const Tuple *tuples, size_t count, const int *order, size_t order_count, Tuple *result)
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
        size_t found = 0;

        for (j = 0; j < count; j++) {
            if (tuples[j].key == order[i]) {
                result[i] = tuples[j];
                found = 1;
                break;
            }
        }
        if (found == 0) {
            return -1;
        }
    }

    return 0;
}

int main(void)
{
    Tuple tuples[] = { {1, 9}, {4, 3}, {2, 10}, {3, 2} };
    int order[] = { 1, 4, 2, 3 };
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

    printf("[");
    for (i = 0; i < count; i++) {
        printf("(%d, %d)", result[i].key, result[i].value);
        if (i < count - 1) {
            printf(", ");
        }
    }
    printf("]\n");

    free(result);
    return EXIT_SUCCESS;
}