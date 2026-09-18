#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    int value;
} Tuple;

Tuple* rearrange_tuples(const Tuple *tuples, size_t tuple_count, const char **order, size_t order_count, size_t *out_count) {
    if (!tuples || !order || !out_count) {
        return NULL;
    }

    Tuple *result = (Tuple *)malloc(order_count * sizeof(Tuple));
    if (!result) {
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < order_count; i++) {
        if (!order[i]) {
            continue;
        }
        for (size_t j = 0; j < tuple_count; j++) {
            if (tuples[j].key && strcmp(order[i], tuples[j].key) == 0) {
                result[count].key = tuples[j].key;
                result[count].value = tuples[j].value;
                count++;
                break;
            }
        }
    }

    *out_count = count;
    return result;
}

int main(void) {
    Tuple tuples[] = {
        {"banana", 20},
        {"cherry", 30},
        {"apple", 10},
        {"date", 40}
    };
    size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);

    const char *order[] = {"apple", "date", "banana"};
    size_t order_count = sizeof(order) / sizeof(order[0]);

    size_t out_count = 0;
    Tuple *rearranged = rearrange_tuples(tuples, tuple_count, order, order_count, &out_count);

    if (!rearranged) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < out_count; i++) {
        printf("%s: %d\n", rearranged[i].key, rearranged[i].value);
    }

    free(rearranged);
    return EXIT_SUCCESS;
}