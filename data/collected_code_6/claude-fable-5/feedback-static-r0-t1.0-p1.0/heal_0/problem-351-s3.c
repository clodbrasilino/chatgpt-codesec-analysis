#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool find_first_element_k_times(const int *arr, size_t n, size_t k, int *result)
{
    if (arr == NULL || result == NULL || n == 0U || k == 0U)
    {
        return false;
    }

    for (size_t i = 0U; i < n; i++)
    {
        size_t count = 0U;

        for (size_t j = 0U; j < n; j++)
        {
            if (arr[j] == arr[i])
            {
                count++;
            }
        }

        if (count == k)
        {
            *result = arr[i];
            return true;
        }
    }

    return false;
}

int main(void)
{
    const int arr[] = { 1, 7, 4, 3, 4, 8, 7 };
    const size_t n = sizeof(arr) / sizeof(arr[0]);
    const size_t k = 2U;
    int result = 0;

    if (find_first_element_k_times(arr, n, k, &result))
    {
        if (printf("First element occurring %zu times: %d\n", k, result) < 0)
        {
            return EXIT_FAILURE;
        }
    }
    else
    {
        if (printf("No element occurs %zu times in the array.\n", k) < 0)
        {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}