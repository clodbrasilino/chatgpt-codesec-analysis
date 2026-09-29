#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[32];
} Tuple;

Tuple* rearrange_tuples(Tuple* tuples, size_t tuple_count, const int* ordered_ids, size_t id_count) {
    if (tuples == NULL || ordered_ids == NULL || tuple_count == 0 || id_count == 0) {
        return NULL;
    }

    Tuple* result = (Tuple*)malloc(tuple_count * sizeof(Tuple));
    if (result == NULL) {
        return NULL;
    }

    size_t result_idx = 0;

    for (size_t i = 0; i < id_count; i++) {
        for (size_t j = 0; j < tuple_count; j++) {
            if (tuples[j].id == ordered_ids[i]) {
                result[result_idx].id = tuples[j].id;
                strncpy(result[result_idx].name, tuples[j].name, sizeof(result[result_idx].name) - 1);
                result[result_idx].name[sizeof(result[result_idx].name) - 1] = '\0';
                result_idx++;
                break;
            }
        }
    }

    for (size_t i = 0; i < tuple_count; i++) {
        int found = 0;
        for (size_t j = 0; j < id_count; j++) {
            if (tuples[i].id == ordered_ids[j]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            result[result_idx].id = tuples[i].id;
            strncpy(result[result_idx].name, tuples[i].name, sizeof(result[result_idx].name) - 1);
            result[result_idx].name[sizeof(result[result_idx].name) - 1] = '\0';
            result_idx++;
        }
    }

    return result;
}

int main() {
    Tuple tuples[] = {
        {5, "five"},
        {1, "one"},
        {3, "three"},
        {2, "two"},
        {4, "four"}
    };
    size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);

    int ordered_ids[] = {2, 4, 1};
    size_t id_count = sizeof(ordered_ids) / sizeof(ordered_ids[0]);

    Tuple* rearranged = rearrange_tuples(tuples, tuple_count, ordered_ids, id_count);
    if (rearranged == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < tuple_count; i++) {
        printf("%d: %s\n", rearranged[i].id, rearranged[i].name);
    }

    free(rearranged);
    rearranged = NULL;

    return EXIT_SUCCESS;
}