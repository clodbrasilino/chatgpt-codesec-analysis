#include <stdio.h>
#include <stdlib.h>

int *access_elements(const int *list, size_t list_size, const size_t *indices, size_t num_indices)
{
    if (list == NULL || indices == NULL || num_indices == 0) {
        return NULL;
    }

    int *result = malloc(num_indices * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < num_indices; i++) {
        if (indices[i] >= list_size) {
            free(result);
            return NULL;
        }
        result[i] = list[indices[i]];
    }

    return result;
}

int main(void)
{
    int list[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    size_t list_size = sizeof(list) / sizeof(list[0]);

    size_t indices[] = {0, 2, 4, 7, 9};
    size_t num_indices = sizeof(indices) / sizeof(indices[0]);

    int *result = access_elements(list, list_size, indices, num_indices);

    if (result == NULL) {
        fprintf(stderr, "Error: failed to access elements\n");
        return EXIT_FAILURE;
    }

    printf("Accessed elements: ");
    for (size_t i = 0; i < num_indices; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
    return EXIT_SUCCESS;
}