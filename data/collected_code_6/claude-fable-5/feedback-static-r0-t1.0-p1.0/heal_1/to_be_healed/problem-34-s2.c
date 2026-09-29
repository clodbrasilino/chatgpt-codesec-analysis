#include <stdio.h>
#include <stdlib.h>

int find_missing_number(const int *arr, size_t size, int *missing)
{
    size_t low;
    size_t high;
    /* Possible weaknesses found:
     *  The scope of the variable 'mid' can be reduced. [variableScope]
     */
    size_t mid;

    if (arr == NULL || missing == NULL || size == 0U) {
        return -1;
    }

    low = 0U;
    high = size - 1U;

    if (arr[low] != (int)low + 1) {
        *missing = 1;
        return 0;
    }

    if (arr[high] == (int)size) {
        return -1;
    }

    while (low < high) {
        mid = low + ((high - low) / 2U);
        if (arr[mid] == (int)mid + 1) {
            low = mid + 1U;
        } else {
            high = mid;
        }
    }

    *missing = (int)low + 1;
    return 0;
}

int main(void)
{
    int arr[] = {1, 2, 3, 5, 6, 7, 8};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int missing = 0;
    int result;

    result = find_missing_number(arr, size, &missing);

    if (result == 0) {
        if (printf("Missing number: %d\n", missing) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("No missing number found\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}