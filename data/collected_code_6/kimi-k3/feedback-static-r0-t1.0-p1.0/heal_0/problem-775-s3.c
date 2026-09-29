#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

bool check_odd_indices_odd_numbers(const int *arr, size_t size)
{
    if (arr == NULL)
    {
        return false;
    }

    for (size_t i = 1; i < size; i += 2)
    {
        if (arr[i] % 2 == 0)
        {
            return false;
        }
    }

    return true;
}

int main(void)
{
    int arr1[] = {2, 3, 4, 5, 6, 7};
    int arr2[] = {2, 3, 4, 6, 6, 7};
    int arr3[] = {1, 2, 3, 4};

    printf("%d\n", check_odd_indices_odd_numbers(arr1, sizeof(arr1) / sizeof(arr1[0])));
    printf("%d\n", check_odd_indices_odd_numbers(arr2, sizeof(arr2) / sizeof(arr2[0])));
    printf("%d\n", check_odd_indices_odd_numbers(arr3, sizeof(arr3) / sizeof(arr3[0])));

    return 0;
}