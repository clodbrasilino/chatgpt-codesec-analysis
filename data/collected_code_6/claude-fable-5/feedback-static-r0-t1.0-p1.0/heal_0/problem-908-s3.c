#include <stdio.h>
#include <stdlib.h>

int find_fixed_point(const int *arr, size_t size)
{
    size_t low = 0;
    size_t high;

    if (arr == NULL || size == 0U) {
        return -1;
    }

    high = size - 1U;

    while (low <= high) {
        size_t mid = low + ((high - low) / 2U);

        if (arr[mid] == (int)mid) {
            return (int)mid;
        } else if (arr[mid] < (int)mid) {
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
    int arr[] = {-10, -5, 2, 3, 7};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int result;

    result = find_fixed_point(arr, size);

    if (result >= 0) {
        if (printf("Fixed point found at index: %d\n", result) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("No fixed point found in the array.\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}