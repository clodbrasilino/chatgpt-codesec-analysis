#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

size_t remove_even(int *arr, size_t size)
{
    size_t read;
    size_t write;

    if (arr == NULL) {
        return 0;
    }

    write = 0;
    for (read = 0; read < size; read++) {
        if (write >= size) {
            break;
        }
        if (arr[read] % 2 != 0) {
            arr[write] = arr[read];
            write++;
        }
    }

    return write;
}

int main(void)
{
    int *arr;
    size_t size;
    size_t new_size;
    size_t i;

    size = 10;

    if (size == 0 || size > SIZE_MAX / sizeof(*arr)) {
        fprintf(stderr, "Invalid array size\n");
        return EXIT_FAILURE;
    }

    arr = malloc(size * sizeof(*arr));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < size; i++) {
        if (i >= (size_t)INT_MAX) {
            fprintf(stderr, "Value out of range\n");
            free(arr);
            arr = NULL;
            return EXIT_FAILURE;
        }
        arr[i] = (int)(i + 1);
    }

    printf("Original list: ");
    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    new_size = remove_even(arr, size);

    if (new_size > size) {
        fprintf(stderr, "Unexpected result size\n");
        free(arr);
        arr = NULL;
        return EXIT_FAILURE;
    }

    printf("List after removing even numbers: ");
    for (i = 0; i < new_size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    arr = NULL;

    return EXIT_SUCCESS;
}