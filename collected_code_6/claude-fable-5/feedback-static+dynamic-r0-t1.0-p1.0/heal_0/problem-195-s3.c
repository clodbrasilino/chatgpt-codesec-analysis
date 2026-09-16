#include <stdio.h>
#include <stddef.h>

int find_first_position(const int *arr, size_t size, int target)
{
    if (arr == NULL || size == 0) {
        return -1;
    }

    size_t low = 0;
    size_t high = size - 1;
    int result = -1;

    while (low <= high) {
        size_t mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            result = (int)mid;
            if (mid == 0) {
                break;
            }
            high = mid - 1;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            if (mid == 0) {
                break;
            }
            high = mid - 1;
        }
    }

    return result;
}

int main(void)
{
    int arr[] = {1, 2, 2, 2, 3, 4, 5, 5, 6};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int target = 2;

    int pos = find_first_position(arr, size, target);

    if (pos >= 0) {
        if (printf("First position of %d is %d\n", target, pos) < 0) {
            return 1;
        }
    } else {
        if (printf("Element %d not found\n", target) < 0) {
            return 1;
        }
    }

    target = 5;
    pos = find_first_position(arr, size, target);

    if (pos >= 0) {
        if (printf("First position of %d is %d\n", target, pos) < 0) {
            return 1;
        }
    } else {
        if (printf("Element %d not found\n", target) < 0) {
            return 1;
        }
    }

    target = 7;
    pos = find_first_position(arr, size, target);

    if (pos >= 0) {
        if (printf("First position of %d is %d\n", target, pos) < 0) {
            return 1;
        }
    } else {
        if (printf("Element %d not found\n", target) < 0) {
            return 1;
        }
    }

    return 0;
}