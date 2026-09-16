#include <stdio.h>
#include <stdlib.h>

size_t find_max_indices(const int *arr, size_t size, size_t **indices)
{
    size_t i;
    size_t count;
    int max_val;
    size_t *temp_indices;

    if (arr == NULL || indices == NULL || size == 0) {
        if (indices != NULL) {
            *indices = NULL;
        }
        return 0;
    }

    max_val = arr[0];
    for (i = 1; i < size; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }

    count = 0;
    for (i = 0; i < size; i++) {
        if (arr[i] == max_val) {
            count++;
        }
    }

    temp_indices = (size_t *)malloc(count * sizeof(size_t));
    if (temp_indices == NULL) {
        *indices = NULL;
        return 0;
    }

    count = 0;
    for (i = 0; i < size; i++) {
        if (arr[i] == max_val) {
            temp_indices[count] = i;
            count++;
        }
    }

    *indices = temp_indices;
    return count;
}

int main(void)
{
    int arr[] = {1, 5, 3, 5, 2, 5, 4};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    size_t *indices = NULL;
    size_t count;
    size_t i;

    count = find_max_indices(arr, size, &indices);

    if (indices == NULL && count == 0) {
        fprintf(stderr, "Error: Failed to find maximum indices\n");
        return EXIT_FAILURE;
    }

    printf("Array: ");
    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("Maximum value indices: ");
    for (i = 0; i < count; i++) {
        printf("%zu ", indices[i]);
    }
    printf("\n");

    printf("Number of occurrences: %zu\n", count);

    free(indices);
    indices = NULL;

    return EXIT_SUCCESS;
}