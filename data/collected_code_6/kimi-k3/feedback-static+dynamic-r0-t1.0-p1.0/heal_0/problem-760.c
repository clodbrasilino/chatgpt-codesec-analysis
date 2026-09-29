#include <stdio.h>
#include <stdbool.h>

bool has_single_distinct_element(const int arr[], size_t size)
{
    if (arr == NULL || size == 0)
    {
        return false;
    }

    for (size_t i = 1; i < size; i++)
    {
        if (arr[i] != arr[0])
        {
            return false;
        }
    }

    return true;
}

int main(void)
{
    int arr1[] = {5, 5, 5, 5};
    int arr2[] = {5, 5, 3, 5};
    int arr3[] = {7};

    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    size_t size3 = sizeof(arr3) / sizeof(arr3[0]);

    printf("Array 1: %s\n", has_single_distinct_element(arr1, size1) ? "true" : "false");
    printf("Array 2: %s\n", has_single_distinct_element(arr2, size2) ? "true" : "false");
    printf("Array 3: %s\n", has_single_distinct_element(arr3, size3) ? "true" : "false");

    return 0;
}