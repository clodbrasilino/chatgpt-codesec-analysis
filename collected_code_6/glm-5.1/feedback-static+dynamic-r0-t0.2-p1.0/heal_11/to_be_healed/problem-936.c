#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char name[32];
} Tuple;

Tuple* rearrange_tuples(const Tuple* tuples, size_t tuple_count, const int* order, size_t order_count) {
    if (tuples == NULL || order == NULL || tuple_count == 0 || order_count == 0) {
        return NULL;
    }

    Tuple* result = malloc(tuple_count * sizeof(Tuple));
    if (result == NULL) {
        return NULL;
    }

    size_t* positions = malloc(tuple_count * sizeof(size_t));
    if (positions == NULL) {
        free(result);
        return NULL;
    }

    for (size_t i = 0; i < tuple_count; i++) {
        positions[i] = tuple_count;
    }

    for (size_t i = 0; i < tuple_count; i++) {
        for (size_t j = 0; j < order_count && j < tuple_count; j++) {
            if (tuples[i].id == order[j]) {
                positions[i] = j;
                break;
            }
        }
    }

    size_t current_index = 0;
    for (size_t i = 0; i < order_count && current_index < tuple_count; i++) {
        for (size_t j = 0; j < tuple_count; j++) {
            if (positions[j] == i) {
                result[current_index++] = tuples[j];
            }
        }
    }

    for (size_t i = 0; i < tuple_count; i++) {
        if (positions[i] == tuple_count) {
            result[current_index++] = tuples[i];
        }
    }

    free(positions);
    return result;
}

int main() {
    Tuple tuples[] = {
        {3, "Charlie"},
        {1, "Alice"},
        {4, "David"},
        {2, "Bob"}
    };
    const int order[] = {2, 1, 3};
    size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);
    size_t order_count = sizeof(order) / sizeof(order[0]);

    Tuple* rearranged = rearrange_tuples(tuples, tuple_count, order, order_count);
    if (rearranged != NULL) {
        for (size_t i = 0; i < tuple_count; i++) {
            printf("%d: %s\n", rearranged[i].id, rearranged[i].name);
        }
        free(rearranged);
    }

    return 0;
}