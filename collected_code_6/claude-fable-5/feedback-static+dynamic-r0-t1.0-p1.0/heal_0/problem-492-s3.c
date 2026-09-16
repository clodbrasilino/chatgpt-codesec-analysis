#include <stdio.h>
#include <stddef.h>

int binary_search(const int *arr, size_t size, int target)
{
    size_t low;
    size_t high;
    size_t mid;

    if (arr == NULL || size == 0U) {
        return -1;
    }

    low = 0U;
    high = size - 1U;

    while (low <= high) {
        mid = low + ((high - low) / 2U);

        if (arr[mid] == target) {
            return (int)mid;
        } else if (arr[mid] < target) {
            low = mid + 1U;
        } else {
            if (mid == 0U) {
                break;
            }
            high = mid - 1U;
        }
    }

    return -1;
}

int main(void)
{
    int arr[] = {2, 4, 7, 10, 15, 23, 42, 56, 78, 91};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int target = 23;
    int result;

    result = binary_search(arr, size, target);

    if (result >= 0) {
        if (printf("Element %d found at index %d\n", target, result) < 0) {
            return 1;
        }
    } else {
        if (printf("Element %d not found in the array\n", target) < 0) {
            return 1;
        }
    }

    return 0;
}