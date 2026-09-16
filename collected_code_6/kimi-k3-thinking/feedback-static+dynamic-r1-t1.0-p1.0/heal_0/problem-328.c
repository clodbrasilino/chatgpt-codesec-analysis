#include <stdio.h>
#include <stdlib.h>

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

int rotate_left(int *arr, size_t size, size_t positions)
{
    if (arr == NULL)
    {
        return -1;
    }

    if (size < 2)
    {
        return 0;
    }

    positions %= size;

    if (positions == 0)
    {
        return 0;
    }

    reverse_range(arr, 0, positions - 1);
    reverse_range(arr, positions, size - 1);
    reverse_range(arr, 0, size - 1);

    return 0;
}

int main(void)
{
    const size_t size = 7;
    const size_t positions = 2;
    int *arr = malloc(size * sizeof(*arr));
    size_t i;

    if (arr == NULL)
    {
        fprintf(stderr, "Error: memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < size; i++)
    {
        arr[i] = (int)(i + 1);
    }

    printf("Original list: ");
    for (i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    if (rotate_left(arr, size, positions) != 0)
    {
        fprintf(stderr, "Error: failed to rotate the list\n");
        free(arr);
        return EXIT_FAILURE;
    }

    printf("List after rotating left by %zu positions: ", positions);
    for (i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    arr = NULL;

    return EXIT_SUCCESS;
}