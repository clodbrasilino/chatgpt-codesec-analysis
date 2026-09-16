#include <stdio.h>
#include <stdlib.h>

int binary_search(const int *arr, size_t size, int target, size_t *index)
{
    size_t low;
    size_t high;
    /* Possible weaknesses found:
     *  The scope of the variable 'mid' can be reduced. [variableScope]
     */
    size_t mid;

    if (arr == NULL || size == 0 || index == NULL) {
        return -1;
    }

    low = 0;
    high = size - 1;

    while (low <= high) {
        mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            *index = mid;
            return 0;
        }

        if (arr[mid] < target) {
            low = mid + 1;
        } else {
            if (mid == 0) {
                break;
            }
            high = mid - 1;
        }
    }

    return -1;
}

int main(void)
{
    int arr[] = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int target = 23;
    size_t index = 0;
    int result;

    result = binary_search(arr, size, target, &index);

    if (result == 0) {
        if (printf("Element %d found at index %zu\n", target, index) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("Element %d not found in the array\n", target) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}