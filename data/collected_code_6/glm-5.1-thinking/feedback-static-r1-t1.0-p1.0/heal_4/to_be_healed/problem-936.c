#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    int key;
    int value;
} Tuple;

int rearrange_tuples(Tuple *tuples, size_t num_tuples, const int *order, size_t order_size) {
    if (tuples == NULL || (order_size > 0 && order == NULL)) {
        return -1;
    }

    if (num_tuples == 0) {
        return 0;
    }

    if (num_tuples > SIZE_MAX / sizeof(Tuple)) {
        return -1;
    }

    size_t dest_capacity = num_tuples * sizeof(Tuple);

    Tuple *buffer = malloc(dest_capacity);
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
                if (write_idx >= num_tuples) {
                    free(buffer);
                    free(processed);
                    return -1;
                }
                buffer[write_idx++] = tuples[j];
                processed[j] = 1;
            }
        }
    }

    for (size_t j = 0; j < num_tuples; ++j) {
        if (!processed[j]) {
            if (write_idx >= num_tuples) {
                free(buffer);
                free(processed);
                return -1;
            }
            buffer[write_idx++] = tuples[j];
        }
    }

    size_t copy_size = write_idx * sizeof(Tuple);
    if (copy_size / sizeof(Tuple) != write_idx || copy_size > dest_capacity) {
        free(buffer);
        free(processed);
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(tuples, buffer, copy_size);
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

    if (rearrange_tuples(tuples, num_tuples, order, order_size) == 0) {
        for (size_t i = 0; i < num_tuples; ++i) {
            printf("(%d, %d)\n", tuples[i].key, tuples[i].value);
        }
    }

    return 0;
}