#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <limits.h>

bool is_decreasing(const int *arr, size_t size)
{
    if (arr == NULL || size < 2) {
        return false;
    }

    for (size_t i = 1; i < size; i++) {
        if (arr[i] >= arr[i - 1]) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    size_t size = 0;

    printf("Enter the number of elements: ");
    if (scanf("%zu", &size) != 1 || size < 2) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    int *arr = malloc(size * sizeof(*arr));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    printf("Enter %zu integers:\n", size);
    for (size_t i = 0; i < size; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            fprintf(stderr, "Invalid input.\n");
            free(arr);
            return EXIT_FAILURE;
        }
    }

    if (is_decreasing(arr, size)) {
        printf("The sequence has a decreasing trend.\n");
    } else {
        printf("The sequence does not have a decreasing trend.\n");
    }

    free(arr);
    return EXIT_SUCCESS;
}