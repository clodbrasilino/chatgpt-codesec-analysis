#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int rotate_right(int *arr, size_t n, size_t k)
{
    int *temp;
    size_t i;
    size_t total_size;

    if (arr == NULL || n == 0) {
        return -1;
    }

    if (n > SIZE_MAX / sizeof(*temp)) {
        return -1;
    }

    total_size = n * sizeof(*temp);

    k = k % n;
    if (k == 0) {
        return 0;
    }

    temp = malloc(total_size);
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

int main(void)
{
    int list[] = {1, 2, 3, 4, 5, 6, 7};
    size_t n = sizeof(list) / sizeof(list[0]);
    size_t k = 3;
    size_t i;

    printf("Original list: ");
    for (i = 0; i < n; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");

    if (rotate_right(list, n, k) != 0) {
        fprintf(stderr, "Rotation failed\n");
        return EXIT_FAILURE;
    }

    printf("Rotated list:  ");
    for (i = 0; i < n; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");

    return EXIT_SUCCESS;
}