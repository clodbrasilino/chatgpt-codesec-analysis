#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int *remove_consecutive_duplicates(const int *arr, size_t size, size_t *new_size)
{
    int *result;
    size_t i;
    size_t j;

    if (new_size == NULL) {
        return NULL;
    }
    *new_size = 0;

    if (arr == NULL || size == 0) {
        return NULL;
    }

    if (size > SIZE_MAX / sizeof(*result)) {
        return NULL;
    }

    result = malloc(size * sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    result[0] = arr[0];
    j = 1;

    for (i = 1; i < size; i++) {
        if (arr[i] != arr[i - 1]) {
            result[j] = arr[i];
            j++;
        }
    }

    *new_size = j;
    return result;
}

int main(void)
{
    int arr[] = {1, 1, 2, 2, 2, 3, 4, 4, 5, 5, 1};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    size_t new_size = 0;
    size_t i;
    int *result;

    result = remove_consecutive_duplicates(arr, size, &new_size);
    if (result == NULL) {
        fprintf(stderr, "Error: failed to process the list\n");
        return EXIT_FAILURE;
    }

    printf("Original list: ");
    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("Without consecutive duplicates: ");
    for (i = 0; i < new_size; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
    result = NULL;

    return EXIT_SUCCESS;
}