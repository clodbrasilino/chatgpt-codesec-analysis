#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

size_t removeDuplicates(int *arr, size_t n)
{
    size_t i, j, k;

    if (arr == NULL || n == 0)
    {
        return 0;
    }

    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (arr[i] == arr[j])
            {
                for (k = j; k + 1 < n; k++)
                {
                    arr[k] = arr[k + 1];
                }
                n--;
                j--;
            }
        }
    }

    return n;
}

int main(void)
{
    size_t n, i, newSize;
    int *arr = NULL;

    printf("Enter the number of elements: ");
    if (scanf("%zu", &n) != 1 || n == 0 || n > SIZE_MAX / sizeof(int))
    {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    printf("Enter %zu elements: ", n);
    for (i = 0; i < n; i++)
    {
        if (scanf("%d", &arr[i]) != 1)
        {
            fprintf(stderr, "Invalid input.\n");
            free(arr);
            arr = NULL;
            return EXIT_FAILURE;
        }
    }

    newSize = removeDuplicates(arr, n);

    printf("List after removing duplicates: ");
    for (i = 0; i < newSize; i++)
    {
        printf("%d%s", arr[i], (i + 1 < newSize) ? " " : "");
    }
    printf("\n");

    free(arr);
    arr = NULL;

    return EXIT_SUCCESS;
}