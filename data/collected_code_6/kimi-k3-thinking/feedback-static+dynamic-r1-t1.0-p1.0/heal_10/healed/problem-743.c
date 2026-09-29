#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int rotate_right(int *arr, size_t size, size_t positions)
{
    int *temp;
    size_t arr_bytes;
    size_t tail_bytes;
    size_t i;

    if (arr == NULL || size == 0)
    {
        return -1;
    }

    if (size > SIZE_MAX / sizeof(*arr))
    {
        return -1;
    }
    arr_bytes = size * sizeof(*arr);

    positions %= size;
    if (positions == 0)
    {
        return 0;
    }

    if (positions > SIZE_MAX / sizeof(*temp))
    {
        return -1;
    }
    tail_bytes = positions * sizeof(*temp);

    if (tail_bytes > arr_bytes)
    {
        return -1;
    }

    temp = (int *)malloc(tail_bytes);
    if (temp == NULL)
    {
        return -1;
    }

    for (i = 0; i < positions; i++)
    {
        temp[i] = arr[size - positions + i];
    }

    for (i = size - positions; i > 0; i--)
    {
        arr[positions + i - 1] = arr[i - 1];
    }

    for (i = 0; i < positions; i++)
    {
        arr[i] = temp[i];
    }

    free(temp);
    temp = NULL;

    return 0;
}

int main(void)
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    const size_t size = sizeof(arr) / sizeof(arr[0]);
    const size_t positions = 3;
    size_t i;

    printf("Original list: ");
    for (i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    if (rotate_right(arr, size, positions) != 0)
    {
        fprintf(stderr, "Error: failed to rotate the list.\n");
        return EXIT_FAILURE;
    }

    printf("Rotated list:  ");
    for (i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return EXIT_SUCCESS;
}