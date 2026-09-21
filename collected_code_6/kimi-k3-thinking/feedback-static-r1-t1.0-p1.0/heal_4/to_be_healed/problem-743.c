#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int rotate_right(int *arr, size_t size, size_t positions)
{
    int *temp;
    size_t temp_capacity;
    size_t copy_size;
    size_t move_size;
    size_t arr_size;

    if (arr == NULL || size == 0)
    {
        return -1;
    }

    positions %= size;
    if (positions == 0)
    {
        return 0;
    }

    if (size > SIZE_MAX / sizeof(*arr))
    {
        return -1;
    }
    arr_size = size * sizeof(*arr);

    if (positions > SIZE_MAX / sizeof(*temp))
    {
        return -1;
    }
    temp_capacity = positions * sizeof(*temp);

    temp = (int *)malloc(temp_capacity);
    if (temp == NULL)
    {
        return -1;
    }

    copy_size = temp_capacity;
    if (copy_size > arr_size)
    {
        free(temp);
        temp = NULL;
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temp, arr + (size - positions), copy_size);

    move_size = arr_size - copy_size;
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