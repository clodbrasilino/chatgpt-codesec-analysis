#include <stdio.h>
#include <stdlib.h>

int count_even_elements(const int *arr, size_t size)
{
    int count = 0;
    size_t i;

    if (arr == NULL) {
        return 0;
    }

    for (i = 0; i < size; i++) {
        if (arr[i] % 2 == 0) {
            count++;
        }
    }

    return count;
}

int main(void)
{
    int *arr = NULL;
    size_t size = 0;
    size_t i;
    int result;

    printf("Enter the number of elements: ");
    if (scanf("%zu", &size) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (size == 0) {
        printf("Number of even elements: 0\n");
        return EXIT_SUCCESS;
    }

    arr = (int *)malloc(size * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Enter %zu elements: ", size);
    for (i = 0; i < size; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            fprintf(stderr, "Invalid input\n");
            free(arr);
            arr = NULL;
            return EXIT_FAILURE;
        }
    }

    result = count_even_elements(arr, size);
    printf("Number of even elements: %d\n", result);

    free(arr);
    arr = NULL;

    return EXIT_SUCCESS;
}