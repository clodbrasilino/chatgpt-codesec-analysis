#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int rotate_right(int *arr, size_t n, size_t k)
{
    int *temp;
    size_t i;
    size_t bytes;

    if (arr == NULL || n == 0) {
        return -1;
    }

    k = k % n;
    if (k == 0) {
        return 0;
    }

    if (n > SIZE_MAX / sizeof(*temp)) {
        return -1;
    }

    bytes = n * sizeof(*temp);

    temp = malloc(bytes);
    if (temp == NULL) {
        return -1;
    }

    for (i = 0; i < n; i++) {
        temp[(i + k) % n] = arr[i];
    }

    for (i = 0; i < n; i++) {
        arr[i] = temp[i];
    }

    free(temp);

    return 0;
}

static void print_array(const int *arr, size_t n)
{
    size_t i;

    if (arr == NULL) {
        return;
    }

    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void)
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    size_t k = 3;

    printf("Original array: ");
    print_array(arr, n);

    if (rotate_right(arr, n, k) != 0) {
        fprintf(stderr, "Rotation failed\n");
        return EXIT_FAILURE;
    }

    printf("Rotated array:  ");
    print_array(arr, n);

    return EXIT_SUCCESS;
}