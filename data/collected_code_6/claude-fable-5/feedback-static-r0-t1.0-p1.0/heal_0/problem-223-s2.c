#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

static size_t lower_bound(const int arr[], size_t n, int value)
{
    size_t low = 0;
    size_t high = n;

    while (low < high)
    {
        size_t mid = low + (high - low) / 2u;
        if (arr[mid] < value)
        {
            low = mid + 1u;
        }
        else
        {
            high = mid;
        }
    }
    return low;
}

static size_t upper_bound(const int arr[], size_t n, int value)
{
    size_t low = 0;
    size_t high = n;

    while (low < high)
    {
        size_t mid = low + (high - low) / 2u;
        if (arr[mid] <= value)
        {
            low = mid + 1u;
        }
        else
        {
            high = mid;
        }
    }
    return low;
}

bool is_majority(const int arr[], size_t n, int candidate)
{
    size_t first;
    size_t last;
    size_t count;

    if ((arr == NULL) || (n == 0u))
    {
        return false;
    }

    first = lower_bound(arr, n, candidate);
    last = upper_bound(arr, n, candidate);
    count = last - first;

    return count > (n / 2u);
}

bool find_majority(const int arr[], size_t n, int *result)
{
    int candidate;

    if ((arr == NULL) || (n == 0u) || (result == NULL))
    {
        return false;
    }

    candidate = arr[n / 2u];

    if (is_majority(arr, n, candidate))
    {
        *result = candidate;
        return true;
    }
    return false;
}

int main(void)
{
    int arr1[] = {1, 2, 3, 3, 3, 3, 10};
    int arr2[] = {1, 1, 2, 4, 4, 4, 6, 6};
    int arr3[] = {5, 5, 5, 5, 5};
    size_t n1 = sizeof(arr1) / sizeof(arr1[0]);
    size_t n2 = sizeof(arr2) / sizeof(arr2[0]);
    size_t n3 = sizeof(arr3) / sizeof(arr3[0]);
    int majority;

    if (find_majority(arr1, n1, &majority))
    {
        if (printf("Majority element in arr1: %d\n", majority) < 0)
        {
            return 1;
        }
    }
    else
    {
        if (printf("No majority element in arr1\n") < 0)
        {
            return 1;
        }
    }

    if (find_majority(arr2, n2, &majority))
    {
        if (printf("Majority element in arr2: %d\n", majority) < 0)
        {
            return 1;
        }
    }
    else
    {
        if (printf("No majority element in arr2\n") < 0)
        {
            return 1;
        }
    }

    if (find_majority(arr3, n3, &majority))
    {
        if (printf("Majority element in arr3: %d\n", majority) < 0)
        {
            return 1;
        }
    }
    else
    {
        if (printf("No majority element in arr3\n") < 0)
        {
            return 1;
        }
    }

    return 0;
}