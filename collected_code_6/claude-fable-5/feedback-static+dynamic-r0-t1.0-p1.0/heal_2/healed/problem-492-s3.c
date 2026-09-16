#include <stdio.h>
#include <stddef.h>

int binary_search(const int *arr, size_t size, int target)
{
    size_t low;
    size_t high;

    if (arr == NULL || size == 0U) {
        return -1;
    }

    low = 0U;
    high = size;

    while (low < high) {
        size_t mid = low + ((high - low) / 2U);

        if (arr[mid] == target) {
            return (int)mid;
        } else if (arr[mid] < target) {
            low = mid + 1U;
        } else {
            high = mid;
        }
    }

    return -1;
}

int main(void)
{
    int arr[] = {2, 4, 7, 10, 15, 23, 42, 56, 78, 91};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int targets[] = {23, 2, 91, 5, 100};
    size_t num_targets = sizeof(targets) / sizeof(targets[0]);
    size_t i;
    int result;

    for (i = 0U; i < num_targets; i++) {
        result = binary_search(arr, size, targets[i]);

        if (result >= 0) {
            if (printf("Element %d found at index %d\n", targets[i], result) < 0) {
                return 1;
            }
        } else {
            if (printf("Element %d not found in the array\n", targets[i]) < 0) {
                return 1;
            }
        }
    }

    return 0;
}