#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

static int find_tuple_index(const Tuple *tuples, size_t count, int key)
{
    size_t i;
    for (i = 0; i < count; i++) {
        if (tuples[i].first == key) {
            return (int)i;
        }
    }
    return -1;
}

static Tuple *rearrange_tuples(const Tuple *tuples, size_t count, const int *order, size_t order_count)
{
    Tuple *result;
    size_t i;
    /* Possible weaknesses found:
     *  The scope of the variable 'idx' can be reduced. [variableScope]
     */
    int idx;

    if (tuples == NULL || order == NULL || count == 0 || order_count == 0) {
        return NULL;
    }

    if (count != order_count) {
        return NULL;
    }

    result = malloc(count * sizeof(Tuple));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < order_count; i++) {
        idx = find_tuple_index(tuples, count, order[i]);
        if (idx < 0) {
            free(result);
            return NULL;
        }
        result[i] = tuples[idx];
    }

    return result;
}

int main(void)
{
    Tuple tuples[] = { {4, 3}, {1, 9}, {2, 10}, {3, 2} };
    int order[] = { 1, 4, 2, 3 };
    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    size_t order_count = sizeof(order) / sizeof(order[0]);
    Tuple *rearranged;
    size_t i;

    rearranged = rearrange_tuples(tuples, count, order, order_count);
    if (rearranged == NULL) {
        fprintf(stderr, "Failed to rearrange tuples\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        if (printf("(%d, %d)\n", rearranged[i].first, rearranged[i].second) < 0) {
            free(rearranged);
            return EXIT_FAILURE;
        }
    }

    free(rearranged);
    return EXIT_SUCCESS;
}