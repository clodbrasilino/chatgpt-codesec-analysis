#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    int key;
    int value;
} Tuple;

int rearrange_tuples(Tuple *tuples, size_t num_tuples, size_t tuples_capacity, const int *order, size_t order_size) {
    if (tuples == NULL || (order_size > 0 && order == NULL)) {
        return -1;
    }

    if (num_tuples == 0) {
        return 0;
    }

    if (num_tuples > tuples_capacity) {
        return -1;
    }

    if (num_tuples > SIZE_MAX / sizeof(Tuple) || tuples_capacity > SIZE_MAX / sizeof(Tuple)) {
        return -1;
    }

    size_t buffer_size = num_tuples * sizeof(Tuple);

    Tuple *buffer = malloc(buffer_size);
    if (buffer == NULL) {
        return -1;
    }

    unsigned char *processed = calloc(num_tuples, sizeof(unsigned char));
    if (processed == NULL) {
        free(buffer);
        return -1;
    }

    size_t write_idx = 0;

    for (size_t i = 0; i < order_size; ++i) {
        for (size_t j = 0; j < num_tuples; ++j) {
            if (!processed[j] && tuples[j].key == order[i]) {
                buffer[write_idx++] = tuples[j];
                processed[j] = 1;
            }
        }
    }

    for (size_t j = 0; j < num_tuples; ++j) {
        if (!processed[j]) {
            buffer[write_idx++] = tuples[j];
        }
    }

    for (size_t i = 0; i < num_tuples; ++i) {
        tuples[i] = buffer[i];
    }

    free(buffer);
    free(processed);

    return 0;
}

int main(void) {
    Tuple tuples[] = {
        {1, 10},
        {3, 30},
        {2, 20},
        {5, 50},
        {4, 40}
    };
    int order[] = {3, 1, 4};
    size_t num_tuples = sizeof(tuples) / sizeof(tuples[0]);
    size_t order_size = sizeof(order) / sizeof(order[0]);
    size_t tuples_capacity = num_tuples;

    if (rearrange_tuples(tuples, num_tuples, tuples_capacity, order, order_size) == 0) {
        for (size_t i = 0; i < num_tuples; ++i) {
            printf("(%d, %d)\n", tuples[i].key, tuples[i].value);
        }
    }

    return 0;
}