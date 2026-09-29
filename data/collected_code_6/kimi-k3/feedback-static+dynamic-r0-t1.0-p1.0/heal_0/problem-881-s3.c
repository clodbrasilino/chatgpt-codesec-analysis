#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int find_first_even_odd_sum(const int *arr, size_t size, int *result)
{
    size_t i;
    int first_even = 0;
    int first_odd = 0;
    int even_found = 0;
    int odd_found = 0;

    if (arr == NULL || result == NULL || size == 0)
    {
        return -1;
    }

    for (i = 0; i < size; i++)
    {
        if (arr[i] % 2 == 0 && !even_found)
        {
            first_even = arr[i];
            even_found = 1;
        }
        else if (arr[i] % 2 != 0 && !odd_found)
        {
            first_odd = arr[i];
            odd_found = 1;
        }

        if (even_found && odd_found)
        {
            break;
        }
    }

    if (!even_found || !odd_found)
    {
        return -1;
    }

    *result = first_even + first_odd;
    return 0;
}

int main(void)
{
    int arr[] = {1, 3, 5, 7, 2, 4, 6, 8};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int result = 0;
    int status;

    status = find_first_even_odd_sum(arr, size, &result);

    if (status == 0)
    {
        printf("Sum of first even and first odd number: %d\n", result);
    }
    else
    {
        fprintf(stderr, "Error: Could not find both even and odd numbers\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}