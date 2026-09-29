#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int index;
    int value;
} Tuple;

int find_min_index_value_record(Tuple *tuples, size_t count, Tuple *result) {
    if (tuples == NULL || count == 0 || result == NULL) {
        return -1;
    }

    size_t min_idx = 0;
    for (size_t i = 1; i < count; i++) {
        if (tuples[i].value < tuples[min_idx].value) {
            min_idx = i;
        } else if (tuples[i].value == tuples[min_idx].value) {
            if (tuples[i].index < tuples[min_idx].index) {
                min_idx = i;
            }
        }
    }

    *result = tuples[min_idx];
    return 0;
}

int main() {
    Tuple tuples[] = {
        {2, 50},
        {1, 20},
        {3, 20},
        {4, 40}
    };
    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    Tuple result;

    if (find_min_index_value_record(tuples, count, &result) == 0) {
        printf("Index: %d, Value: %d\n", result.index, result.value);
    } else {
        printf("Invalid input or empty array.\n");
    }

    return 0;
}