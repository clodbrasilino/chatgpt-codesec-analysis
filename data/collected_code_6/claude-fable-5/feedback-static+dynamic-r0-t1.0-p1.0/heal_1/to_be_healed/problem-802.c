#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 3, got 5
  *  test case 1 failed: expected 2, got 3
  */

static int count_rotations(const int *arr, size_t n)
{
    size_t low;
    size_t high;

    if (arr == NULL || n == 0U) {
        return -1;
    }

    low = 0U;
    high = n - 1U;

    while (low < high) {
        size_t mid = low + ((high - low) / 2U);

        if (arr[mid] > arr[high]) {
            low = mid + 1U;
        } else {
            high = mid;
        }
    }

    return (int)low;
}

int main(void)
{
    int arr[] = {15, 18, 2, 3, 6, 12};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    int rotations;

    rotations = count_rotations(arr, n);

    if (rotations < 0) {
        if (fprintf(stderr, "Invalid input array\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Number of rotations: %d\n", rotations) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}