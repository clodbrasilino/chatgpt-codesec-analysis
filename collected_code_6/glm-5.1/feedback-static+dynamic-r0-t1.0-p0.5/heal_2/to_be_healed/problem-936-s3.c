#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char data[32];
} Tuple;

Tuple* rearrange_tuples(const Tuple* tuples, size_t tuple_count, const int* ordered_ids, size_t id_count) {
    Tuple* result = (Tuple*)malloc(id_count * sizeof(Tuple));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < id_count; i++) {
        result[i].id = ordered_ids[i];
        result[i].data[0] = '\0';
        for (size_t j = 0; j < tuple_count; j++) {
            if (tuples[j].id == ordered_ids[i]) {
                result[i] = tuples[j];
                break;
            }
        }
    }

    return result;
}

int main() {
    Tuple tuples[] = {
        {3, "third"},
        {1, "first"},
        {2, "second"}
    };
    size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);

    int ordered_ids[] = {1, 2, 3};
    size_t id_count = sizeof(ordered_ids) / sizeof(ordered_ids[0]);

    Tuple* rearranged = rearrange_tuples(tuples, tuple_count, ordered_ids, id_count);
    if (rearranged == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < id_count; i++) {
        printf("%d: %s\n", rearranged[i].id, rearranged[i].data);
    }

    free(rearranged);
    rearranged = NULL;

    return EXIT_SUCCESS;
}