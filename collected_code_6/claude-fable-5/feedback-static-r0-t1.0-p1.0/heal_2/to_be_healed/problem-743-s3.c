#include <stdio.h>
#include <stdlib.h>

static void reverse_range(int *arr, size_t start, size_t end)
{
    /* Possible weaknesses found:
     *  The scope of the variable 'tmp' can be reduced. [variableScope]
     */
    int tmp;

    while (start < end) {
        tmp = arr[start];
        arr[start] = arr[end];
        arr[end] = tmp;
        start++;
        end--;
    }
}

int rotate_right(int *arr, size_t n, size_t k)
{
    if (arr == NULL || n == 0) {
        return -1;
    }

    k = k % n;
    if (k == 0) {
        return 0;
    }

    reverse_range(arr, 0, n - 1);
    reverse_range(arr, 0, k - 1);
    reverse_range(arr, k, n - 1);

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