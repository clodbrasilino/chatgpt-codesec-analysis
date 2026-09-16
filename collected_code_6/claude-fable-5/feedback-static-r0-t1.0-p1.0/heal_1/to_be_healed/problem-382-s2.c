#include <stdio.h>
#include <stdlib.h>

int find_rotation_count(const int *arr, size_t n)
{
    size_t low;
    size_t high;
    /* Possible weaknesses found:
     *  The scope of the variable 'mid' can be reduced. [variableScope]
     */
    size_t mid;

    if (arr == NULL || n == 0U) {
        return -1;
    }

    low = 0U;
    high = n - 1U;

    while (low < high) {
        if (arr[low] <= arr[high]) {
            break;
        }
        mid = low + ((high - low) / 2U);
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
    int arr1[] = {15, 18, 2, 3, 6, 12};
    int arr2[] = {7, 9, 11, 12, 5};
    int arr3[] = {1, 2, 3, 4, 5};
    int result;

    result = find_rotation_count(arr1, sizeof(arr1) / sizeof(arr1[0]));
    if (result < 0) {
        (void)fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    (void)printf("Rotations in arr1: %d\n", result);

    result = find_rotation_count(arr2, sizeof(arr2) / sizeof(arr2[0]));
    if (result < 0) {
        (void)fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    (void)printf("Rotations in arr2: %d\n", result);

    result = find_rotation_count(arr3, sizeof(arr3) / sizeof(arr3[0]));
    if (result < 0) {
        (void)fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    (void)printf("Rotations in arr3: %d\n", result);

    return EXIT_SUCCESS;
}