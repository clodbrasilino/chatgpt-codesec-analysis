#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int rotate_right(int *arr, size_t n, size_t k)
{
    int *temp;
    size_t i;

    if (arr == NULL || n == 0) {
        return -1;
    }

    k = k % n;
    if (k == 0) {
        return 0;
    }

    temp = malloc(n * sizeof(*temp));
    if (temp == NULL) {
        return -1;
    }

    for (i = 0; i < n; i++) {
        temp[(i + k) % n] = arr[i];
    }

    memcpy(arr, temp, n * sizeof(*arr));
    free(temp);

    return 0;
}

int main(void)
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    size_t k = 3;
    size_t i;

    printf("Original list: ");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    if (rotate_right(arr, n, k) != 0) {
        fprintf(stderr, "Rotation failed\n");
        return EXIT_FAILURE;
    }

    printf("Rotated list:  ");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return EXIT_SUCCESS;
}