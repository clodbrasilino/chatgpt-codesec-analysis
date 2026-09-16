#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

int count_repeated_items(const Tuple *tuple) {
    if (tuple == NULL || tuple->data == NULL || tuple->size == 0) {
        return 0;
    }

    int repeated_count = 0;
    int *seen = (int *)calloc(tuple->size, sizeof(int));
    if (seen == NULL) {
        return -1;
    }

    for (size_t i = 0; i < tuple->size; i++) {
        if (seen[i]) {
            continue;
        }

        int count = 1;
        for (size_t j = i + 1; j < tuple->size; j++) {
            if (tuple->data[i] == tuple->data[j]) {
                count++;
                seen[j] = 1;
            }
        }

        if (count > 1) {
            repeated_count++;
        }
    }

    free(seen);
    seen = NULL;

    return repeated_count;
}

int main(void) {
    int values[] = {1, 2, 2, 3, 3, 3, 4, 5, 5};
    Tuple tuple;
    tuple.data = values;
    tuple.size = sizeof(values) / sizeof(values[0]);

    int result = count_repeated_items(&tuple);
    if (result >= 0) {
        printf("Number of repeated items: %d\n", result);
    } else {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}