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

    if (arr == NULL || size == 0)
    {
        return -1;
    }

    if (size > SIZE_MAX / sizeof(*arr))
    {
        return -1;
    }

    positions %= size;
    if (positions == 0)
    {
        return 0;
    }

    tail_offset = size - positions;
    copy_size = positions * sizeof(*temp);
    move_size = tail_offset * sizeof(*arr);

    temp = (int *)malloc(copy_size);
    if (temp == NULL)
    {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temp, arr + tail_offset, copy_size);
    memmove(arr + positions, arr, move_size);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(arr, temp, copy_size);

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