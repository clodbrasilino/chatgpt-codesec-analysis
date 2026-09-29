#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int rotate_right(int *arr, size_t size, size_t positions)
{
    int *temp = NULL;
    size_t copy_size;
    size_t move_size;
    size_t tail_offset;
    size_t arr_bytes;

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

    tail_offset = size - positions;
    copy_size = positions * sizeof(*temp);
    move_size = tail_offset * sizeof(*arr);

    if (copy_size > arr_bytes || move_size > arr_bytes ||
        copy_size + move_size > arr_bytes)
    {
        return -1;
    }

    temp = (int *)malloc(copy_size);
    if (temp == NULL)
    {
        return -1;
    }

    if (copy_size > arr_bytes - (tail_offset * sizeof(*arr)))
    {
        free(temp);
        temp = NULL;
        return -1;
    }

    memmove(temp, arr + tail_offset, copy_size);
    memmove(arr + positions, arr, move_size);
    memmove(arr, temp, copy_size);

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