#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char name[50];
} Tuple;

void rearrange_tuples(Tuple* tuples, int tuples_count, const int* order, int order_count, Tuple** rearranged_tuples, int* rearranged_count) {
    if (tuples == NULL || order == NULL || rearranged_tuples == NULL || rearranged_count == NULL) {
        return;
    }

    *rearranged_tuples = (Tuple*)malloc(order_count * sizeof(Tuple));
    if (*rearranged_tuples == NULL) {
        return;
    }

    *rearranged_count = 0;

    for (int i = 0; i < order_count; ++i) {
        for (int j = 0; j < tuples_count; ++j) {
            if (tuples[j].id == order[i]) {
                (*rearranged_tuples)[*rearranged_count] = tuples[j];
                (*rearranged_count)++;
                break;
            }
        }
    }
}

int main(void) {
    Tuple tuples[] = {
        {3, "Charlie"},
        {1, "Alice"},
        {4, "Dave"},
        {2, "Bob"}
    };
    int tuples_count = sizeof(tuples) / sizeof(tuples[0]);

    int order[] = {2, 1, 4, 3};
    int order_count = sizeof(order) / sizeof(order[0]);

    Tuple* rearranged = NULL;
    int rearranged_count = 0;

    rearrange_tuples(tuples, tuples_count, order, order_count, &rearranged, &rearranged_count);

    if (rearranged != NULL) {
        for (int i = 0; i < rearranged_count; ++i) {
            printf("{%d, \"%s\"}\n", rearranged[i].id, rearranged[i].name);
        }
        free(rearranged);
    }

    return 0;
}