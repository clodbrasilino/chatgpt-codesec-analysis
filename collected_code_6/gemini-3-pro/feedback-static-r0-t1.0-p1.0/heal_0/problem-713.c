#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    int* values;
    size_t size;
} Tuple;

bool check_valid_tuple(const Tuple* tuple, int min_valid, int max_valid) {
    if (tuple == NULL || tuple->values == NULL) {
        return false;
    }

    for (size_t i = 0; i < tuple->size; i++) {
        if (tuple->values[i] < min_valid || tuple->values[i] > max_valid) {
            return false;
        }
    }

    return true;
}

int main(void) {
    size_t num_elements = 5;
    int* data = (int*)malloc(num_elements * sizeof(int));
    if (data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    data[0] = 10;
    data[1] = 20;
    data[2] = 30;
    data[3] = 40;
    data[4] = 50;

    Tuple my_tuple = { .values = data, .size = num_elements };

    int min_val = 0;
    int max_val = 100;

    if (check_valid_tuple(&my_tuple, min_val, max_val)) {
        printf("Tuple contains all valid values.\n");
    } else {
        printf("Tuple contains invalid values.\n");
    }

    free(data);
    my_tuple.values = NULL;

    return EXIT_SUCCESS;
}