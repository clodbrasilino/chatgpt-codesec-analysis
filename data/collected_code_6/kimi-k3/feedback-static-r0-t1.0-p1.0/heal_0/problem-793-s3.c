#include <stdio.h>
#include <stddef.h>

int find_last_position(const int arr[], size_t size, int target, size_t *position)
{
    size_t left;
    size_t right;
    size_t mid;
    size_t result;
    int found;

    if (arr == NULL || position == NULL) {
        return -1;
    }

    if (size == 0) {
        return 0;
    }

    left = 0;
    right = size - 1;
    result = 0;
    found = 0;

    while (left <= right) {
        mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            result = mid;
            found = 1;
            left = mid + 1;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            if (mid == 0) {
                break;
            }
            right = mid - 1;
        }
    }

    if (found) {
        *position = result;
        return 1;
    }

    return 0;
}

int main(void)
{
    int arr[] = {1, 2, 2, 2, 3, 4, 4, 5};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int target = 2;
    size_t position;
    int status;

    status = find_last_position(arr, size, target, &position);

    if (status == 1) {
        printf("Last position of %d: %zu\n", target, position);
    } else if (status == 0) {
        printf("Element %d not found\n", target);
    } else {
        printf("Invalid arguments\n");
    }

    return 0;
}