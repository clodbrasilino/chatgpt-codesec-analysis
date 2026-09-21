#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char value[32];
} Tuple;

Tuple* rearrange_tuples(const Tuple* tuples, size_t tuple_count, const int* ordered_ids, size_t id_count) {
    Tuple* result = (Tuple*)malloc(id_count * sizeof(Tuple));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < id_count; i++) {
        int found = 0;
        for (size_t j = 0; j < tuple_count; j++) {
            if (tuples[j].id == ordered_ids[i]) {
                result[i] = tuples[j];
                found = 1;
                break;
            }
        }
        if (!found) {
            result[i].id = -1;
            memset(result[i].value, 0, sizeof(result[i].value));
        }
    }

    return result;
}

int main() {
    Tuple tuples[] = {
        {3, "three"},
        {1, "one"},
        {2, "two"}
    };
    size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);

    int ordered_ids[] = {2, 1, 3};
    size_t id_count = sizeof(ordered_ids) / sizeof(ordered_ids[0]);

    Tuple* rearranged = rearrange_tuples(tuples, tuple_count, ordered_ids, id_count);
    if (rearranged == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < id_count; i++) {
        if (rearranged[i].id != -1) {
            printf("%d: %s\n", rearranged[i].id, rearranged[i].value);
        }
    }

    free(rearranged);
    rearranged = NULL;

    return EXIT_SUCCESS;
}