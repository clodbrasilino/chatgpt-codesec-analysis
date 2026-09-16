#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int index;
    double value;
} Tuple;

int find_min_index_tuple(Tuple *tuples, size_t count, size_t *result_index) {
    if (tuples == NULL || result_index == NULL) {
        return -1;
    }

    if (count == 0) {
        return -2;
    }

    size_t min_idx = 0;
    for (size_t i = 1; i < count; i++) {
        if (tuples[i].value < tuples[min_idx].value) {
            min_idx = i;
        }
    }

    *result_index = min_idx;
    return 0;
}

int main(void) {
    Tuple data[] = {
        {0, 5.4},
        {1, 2.1},
        {2, 8.9},
        {3, 1.7},
        {4, 4.3}
    };
    size_t data_count = sizeof(data) / sizeof(data[0]);
    size_t min_index;

    int ret = find_min_index_tuple(data, data_count, &min_index);

    if (ret == 0) {
        printf("Index of minimum value: %zu\n", min_index);
        printf("Record: Index = %d, Value = %f\n", data[min_index].index, data[min_index].value);
    } else if (ret == -2) {
        printf("Error: Empty tuple list.\n");
    } else {
        printf("Error: Null pointer provided.\n");
    }

    return 0;
}