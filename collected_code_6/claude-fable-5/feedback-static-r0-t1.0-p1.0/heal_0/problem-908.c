#include <stdio.h>
#include <stdlib.h>

int find_fixed_point(const int *arr, size_t size, int *result)
{
    size_t low;
    size_t high;

    if (arr == NULL || result == NULL || size == 0U) {
        return -1;
    }

    low = 0U;
    high = size - 1U;

    while (low <= high) {
        size_t mid = low + ((high - low) / 2U);

        if (arr[mid] == (int)mid) {
            *result = arr[mid];
            return 0;
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
    int arr[] = { -10, -5, 2, 3, 7 };
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int fixed_point = 0;

    if (find_fixed_point(arr, size, &fixed_point) == 0) {
        if (printf("Fixed point found: %d\n", fixed_point) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("No fixed point found.\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}