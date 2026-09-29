#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

bool is_subarray(const int *arr, size_t arr_size, const int *sub, size_t sub_size)
{
    if (arr == NULL || sub == NULL)
    {
        return false;
    }

    if (sub_size == 0)
    {
        return true;
    }

    if (sub_size > arr_size)
    {
        return false;
    }

    for (size_t i = 0; i <= arr_size - sub_size; i++)
    {
        bool match = true;
        for (size_t j = 0; j < sub_size; j++)
        {
            if (arr[i + j] != sub[j])
            {
                match = false;
                break;
            }
        }
        if (match)
        {
            return true;
        }
    }

    return false;
}

int main(void)
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int sub1[] = {3, 4, 5};
    int sub2[] = {4, 6, 7};
    int sub3[] = {6, 7, 8};
    int sub4[] = {9, 10};

    size_t arr_size = sizeof(arr) / sizeof(arr[0]);
    size_t sub1_size = sizeof(sub1) / sizeof(sub1[0]);
    size_t sub2_size = sizeof(sub2) / sizeof(sub2[0]);
    size_t sub3_size = sizeof(sub3) / sizeof(sub3[0]);
    size_t sub4_size = sizeof(sub4) / sizeof(sub4[0]);

    printf("sub1 is %s\n", is_subarray(arr, arr_size, sub1, sub1_size) ? "a subarray" : "not a subarray");
    printf("sub2 is %s\n", is_subarray(arr, arr_size, sub2, sub2_size) ? "a subarray" : "not a subarray");
    printf("sub3 is %s\n", is_subarray(arr, arr_size, sub3, sub3_size) ? "a subarray" : "not a subarray");
    printf("sub4 is %s\n", is_subarray(arr, arr_size, sub4, sub4_size) ? "a subarray" : "not a subarray");

    return 0;
}