#include <stdio.h>
#include <stdbool.h>

int firstElementKTimes(const int *arr, size_t n, size_t k, bool *found)
{
    if (arr == NULL || n == 0 || k == 0 || found == NULL)
    {
        if (found != NULL)
        {
            *found = false;
        }
        return 0;
    }

    for (size_t i = 0; i < n; i++)
    {
        size_t count = 0;
        for (size_t j = 0; j < n; j++)
        {
            if (arr[j] == arr[i])
            {
                count++;
            }
        }
        if (count == k)
        {
            *found = true;
            return arr[i];
        }
    }

    *found = false;
    return 0;
}

int main(void)
{
    int arr[] = {1, 7, 4, 3, 4, 8, 7};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    size_t k = 2;
    bool found = false;

    int result = firstElementKTimes(arr, n, k, &found);

    if (found)
    {
        if (printf("First element occurring %zu times: %d\n", k, result) < 0)
        {
            return 1;
        }
    }
    else
    {
        if (printf("No element occurs exactly %zu times.\n", k) < 0)
        {
            return 1;
        }
    }

    return 0;
}