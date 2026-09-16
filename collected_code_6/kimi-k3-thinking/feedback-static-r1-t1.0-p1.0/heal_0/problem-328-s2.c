#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

static void reverse_range(int *arr, size_t start, size_t end)
{
    while (start < end)
    {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

int rotate_left(int *arr, size_t length, size_t positions)
{
    size_t k;

    if (length == 0)
    {
        return 0;
    }

    if (arr == NULL)
    {
        return -1;
    }

    k = positions % length;
    if (k == 0)
    {
        return 0;
    }

    reverse_range(arr, 0, k - 1);
    reverse_range(arr, k, length - 1);
    reverse_range(arr, 0, length - 1);

    return 0;
}

int main(void)
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    size_t length = sizeof(arr) / sizeof(arr[0]);
    size_t positions = 3;
    size_t i;

    printf("Original: ");
    for (i = 0; i < length; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    if (rotate_left(arr, length, positions) != 0)
    {
        fprintf(stderr, "Error: invalid arguments passed to rotate_left\n");
        return EXIT_FAILURE;
    }

    printf("Rotated:  ");
    for (i = 0; i < length; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return EXIT_SUCCESS;
}