#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int* add_k_elements(const int* original_array, size_t original_size, const int* k_array, size_t k_size, size_t* out_size) {
    if (original_array == NULL || k_array == NULL || out_size == NULL || original_size == 0) {
        return NULL;
    }

    size_t total_elements = original_size * (1 + k_size);
    if (total_elements < original_size) {
        return NULL;
    }

    int* result = (int*)malloc(total_elements * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    size_t index = 0;
    for (size_t i = 0; i < original_size; ++i) {
        result[index++] = original_array[i];
        for (size_t j = 0; j < k_size; ++j) {
            result[index++] = k_array[j];
        }
    }

    *out_size = total_elements;
    return result;
}

int main(void) {
    int original[] = {5, 6, 7};
    size_t original_size = sizeof(original) / sizeof(original[0]);

    int k_elements[] = {1, 2};
    size_t k_size = sizeof(k_elements) / sizeof(k_elements[0]);

    size_t out_size = 0;
    int* result = add_k_elements(original, original_size, k_elements, k_size, &out_size);

    if (result != NULL) {
        for (size_t i = 0; i < out_size; ++i) {
            printf("%d ", result[i]);
        }
        printf("\n");

        free(result);
        result = NULL;
    } else {
        fprintf(stderr, "Memory allocation failed or invalid input.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}