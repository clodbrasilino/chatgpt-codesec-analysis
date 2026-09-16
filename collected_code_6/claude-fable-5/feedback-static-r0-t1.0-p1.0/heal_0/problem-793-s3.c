#include <stdio.h>
#include <stdlib.h>

int find_last_position(const int *arr, size_t size, int target)
{
    if (arr == NULL || size == 0U) {
        return -1;
    }

    size_t low = 0U;
    size_t high = size - 1U;
    int result = -1;

    while (low <= high) {
        size_t mid = low + ((high - low) / 2U);

        if (arr[mid] == target) {
            result = (int)mid;
            low = mid + 1U;
        } else if (arr[mid] < target) {
            low = mid + 1U;
        } else {
            if (mid == 0U) {
                break;
            }
            high = mid - 1U;
        }
    }

    return result;
}

int main(void)
{
    int arr[] = {1, 2, 2, 2, 3, 4, 5, 5, 6};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int target = 2;

    int pos = find_last_position(arr, size, target);

    if (pos >= 0) {
        if (printf("Last position of %d is %d\n", target, pos) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("Element %d not found\n", target) < 0) {
            return EXIT_FAILURE;
        }
    }

    target = 7;
    pos = find_last_position(arr, size, target);

    if (pos >= 0) {
        if (printf("Last position of %d is %d\n", target, pos) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("Element %d not found\n", target) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}