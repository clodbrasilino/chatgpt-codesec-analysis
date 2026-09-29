#include <stdio.h>
#include <stdlib.h>

static void reverse(int *arr, size_t start, size_t end)
{
    while (start < end) {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

int rotate_right(int *arr, size_t size, size_t k)
{
    if (arr == NULL) {
        return -1;
    }
    if (size <= 1) {
        return 0;
    }
    k %= size;
    if (k == 0) {
        return 0;
    }
    reverse(arr, 0, size - 1);
    reverse(arr, 0, k - 1);
    reverse(arr, k, size - 1);
    return 0;
}

int main(void)
{
    const int source[] = {1, 2, 3, 4, 5, 6, 7};
    const size_t size = sizeof(source) / sizeof(source[0]);
    const size_t k = 3;
    int *arr;
    size_t i;
    int status = EXIT_SUCCESS;

    arr = malloc(size * sizeof(*arr));
    if (arr == NULL) {
        fprintf(stderr, "Error: memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < size; i++) {
        arr[i] = source[i];
    }

    printf("Original: ");
    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    if (rotate_right(arr, size, k) != 0) {
        fprintf(stderr, "Error: rotation failed\n");
        status = EXIT_FAILURE;
    } else {
        printf("Rotated:  ");
        for (i = 0; i < size; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }

    free(arr);
    arr = NULL;

    return status;
}