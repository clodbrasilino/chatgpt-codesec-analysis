#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char data[32];
} Tuple;

Tuple* rearrange_tuples(const Tuple* tuples, size_t tuple_count, const int* ordered_ids, size_t id_count) {
    Tuple* result = malloc(id_count * sizeof(Tuple));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < id_count; i++) {
        result[i].id = ordered_ids[i];
        result[i].data[0] = '\0';
        for (size_t j = 0; j < tuple_count; j++) {
            if (tuples[j].id == ordered_ids[i]) {
                result[i].id = tuples[j].id;
                size_t copy_len = strnlen(tuples[j].data, sizeof(tuples[j].data));
                if (copy_len >= sizeof(result[i].data)) {
                    copy_len = sizeof(result[i].data) - 1;
                }
                memcpy(result[i].data, tuples[j].data, copy_len);
                result[i].data[copy_len] = '\0';
                break;
            }
        }
    }

    return result;
}

int main(void) {
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