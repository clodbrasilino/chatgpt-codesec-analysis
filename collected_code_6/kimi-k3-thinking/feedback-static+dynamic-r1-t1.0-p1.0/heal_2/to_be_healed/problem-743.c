#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int rotate_right(int *arr, size_t size, size_t positions)
{
    int *temp;
    size_t arr_bytes;
    size_t temp_bytes;
    size_t tail_bytes;
    size_t head_bytes;

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
    arr_bytes = size * sizeof(*arr);

    if (positions > SIZE_MAX / sizeof(*temp))
    {
        return -1;
    }
    tail_bytes = positions * sizeof(*temp);

    /* Possible weaknesses found:
     *  temp_bytes is assigned 'tail_bytes' here.
     */
    temp_bytes = tail_bytes;
    temp = (int *)malloc(temp_bytes);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (temp == NULL)
    {
        return -1;
    }

    /* Possible weaknesses found:
     *  Condition 'tail_bytes>temp_bytes' is always false
     *  Condition 'tail_bytes>temp_bytes' is always false [knownConditionTrueFalse]
     */
    if (tail_bytes > temp_bytes || tail_bytes > arr_bytes)
    {
        free(temp);
        temp = NULL;
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temp, arr + size - positions, tail_bytes);

    if ((size - positions) > SIZE_MAX / sizeof(*arr))
    {
        free(temp);
        temp = NULL;
        return -1;
    }
    head_bytes = (size - positions) * sizeof(*arr);

    if (head_bytes > arr_bytes - tail_bytes)
    {
        free(temp);
        temp = NULL;
        return -1;
    }
    memmove(arr + positions, arr, head_bytes);

    if (tail_bytes > arr_bytes)
    {
        free(temp);
        temp = NULL;
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(arr, temp, tail_bytes);

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