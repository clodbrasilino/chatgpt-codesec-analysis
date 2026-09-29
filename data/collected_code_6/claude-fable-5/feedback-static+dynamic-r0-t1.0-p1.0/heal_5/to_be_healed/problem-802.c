#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 2, got 3
  *  test case 2 failed: expected 3, got 5
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
        } else if (arr[mid] < arr[high]) {
            high = mid;
        } else {
            high--;
        }
    }

    return (int)low;
}

int main(void)
{
    int arr1[] = {15, 18, 2, 3, 6, 12};
    int arr2[] = {7, 9, 11, 12, 5};
    size_t n1 = sizeof(arr1) / sizeof(arr1[0]);
    size_t n2 = sizeof(arr2) / sizeof(arr2[0]);
    int rotations1;
    int rotations2;

    rotations1 = count_rotations(arr1, n1);
    rotations2 = count_rotations(arr2, n2);

    if (rotations1 < 0 || rotations2 < 0) {
        if (fprintf(stderr, "Invalid input array\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (rotations1 != 2) {
        if (fprintf(stderr, "test case 1 failed: expected 2, got %d\n",
                    rotations1) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (rotations2 != 4) {
        if (fprintf(stderr, "test case 2 failed: expected 4, got %d\n",
                    rotations2) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Number of rotations: %d\n", rotations1) < 0) {
        return EXIT_FAILURE;
    }

    if (printf("Number of rotations: %d\n", rotations2) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}