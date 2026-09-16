#include <stdio.h>
#include <stdlib.h>

int find_minimum(const int *arr, size_t size, int *result)
{
    size_t low;
    size_t high;
    /* Possible weaknesses found:
     *  The scope of the variable 'mid' can be reduced. [variableScope]
     */
    size_t mid;

    if (arr == NULL || result == NULL || size == 0U) {
        return -1;
    }

    low = 0U;
    high = size - 1U;

    while (low < high) {
        mid = low + ((high - low) / 2U);
        if (arr[mid] > arr[high]) {
            low = mid + 1U;
        } else {
            high = mid;
        }
    }

    *result = arr[low];
    return 0;
}

int main(void)
{
    int arr1[] = {4, 5, 6, 7, 0, 1, 2};
    int arr2[] = {3, 4, 5, 1, 2};
    int arr3[] = {11, 13, 15, 17};
    int arr4[] = {2, 1};
    int minimum;
    int status;

    status = find_minimum(arr1, sizeof(arr1) / sizeof(arr1[0]), &minimum);
    if (status == 0) {
        (void)printf("Minimum of array 1: %d\n", minimum);
    } else {
        (void)fprintf(stderr, "Error finding minimum of array 1\n");
        return EXIT_FAILURE;
    }

    status = find_minimum(arr2, sizeof(arr2) / sizeof(arr2[0]), &minimum);
    if (status == 0) {
        (void)printf("Minimum of array 2: %d\n", minimum);
    } else {
        (void)fprintf(stderr, "Error finding minimum of array 2\n");
        return EXIT_FAILURE;
    }

    status = find_minimum(arr3, sizeof(arr3) / sizeof(arr3[0]), &minimum);
    if (status == 0) {
        (void)printf("Minimum of array 3: %d\n", minimum);
    } else {
        (void)fprintf(stderr, "Error finding minimum of array 3\n");
        return EXIT_FAILURE;
    }

    status = find_minimum(arr4, sizeof(arr4) / sizeof(arr4[0]), &minimum);
    if (status == 0) {
        (void)printf("Minimum of array 4: %d\n", minimum);
    } else {
        (void)fprintf(stderr, "Error finding minimum of array 4\n");
        return EXIT_FAILURE;
    }

    status = find_minimum(NULL, 5U, &minimum);
    if (status != 0) {
        (void)printf("Correctly rejected NULL array\n");
    }

    return EXIT_SUCCESS;
}