#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

int* convert_to_set(const int *input_tuple, size_t input_size, size_t *out_set_size) {
    if (!input_tuple || !out_set_size) {
        return NULL;
    }

    if (input_size == 0) {
        *out_set_size = 0;
        return NULL;
    }

    int *set = (int *)malloc(input_size * sizeof(int));
    if (!set) {
        return NULL;
    }

    size_t unique_count = 0;

    for (size_t i = 0; i < input_size; i++) {
        bool is_duplicate = false;
        for (size_t j = 0; j < unique_count; j++) {
            if (input_tuple[i] == set[j]) {
                is_duplicate = true;
                break;
            }
        }

        if (!is_duplicate) {
            set[unique_count] = input_tuple[i];
            unique_count++;
        }
    }

    int *resized_set = (int *)realloc(set, unique_count * sizeof(int));
    if (!resized_set) {
        free(set);
        return NULL;
    }

    *out_set_size = unique_count;
    return resized_set;
}

int main(void) {
    int sample_tuple[] = {1, 2, 2, 3, 4, 4, 5, 1, 6};
    size_t input_size = sizeof(sample_tuple) / sizeof(sample_tuple[0]);
    size_t set_size = 0;

    int *my_set = convert_to_set(sample_tuple, input_size, &set_size);

    if (!my_set && input_size > 0) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < set_size; i++) {
        printf("%d\n", my_set[i]);
    }

    free(my_set);
    return EXIT_SUCCESS;
}