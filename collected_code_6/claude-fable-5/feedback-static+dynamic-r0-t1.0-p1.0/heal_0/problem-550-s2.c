#include <stdio.h>
#include <stdlib.h>

int findMax(const int *arr, int n, int *result)
{
    int low;
    int high;

    if (arr == NULL || n <= 0 || result == NULL) {
        return -1;
    }

    low = 0;
    high = n - 1;

    while (low < high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] > arr[high]) {
            if (arr[mid + 1] > arr[mid]) {
                low = mid + 1;
            } else {
                *result = arr[mid];
                return 0;
            }
        } else {
            high = mid;
        }
    }

    if (n > 1 && arr[n - 1] > arr[0] && arr[low] < arr[n - 1]) {
        *result = arr[n - 1];
    } else {
        *result = arr[low];
    }

    if (arr[high] > *result) {
        *result = arr[high];
    }

    return 0;
}

int main(void)
{
    int arr1[] = {5, 6, 7, 1, 2, 3, 4};
    int arr2[] = {3, 4, 5, 6, 7, 1, 2};
    int arr3[] = {1, 2, 3, 4, 5};
    int arr4[] = {2};
    int max;

    if (findMax(arr1, (int)(sizeof(arr1) / sizeof(arr1[0])), &max) == 0) {
        printf("Maximum: %d\n", max);
    } else {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (findMax(arr2, (int)(sizeof(arr2) / sizeof(arr2[0])), &max) == 0) {
        printf("Maximum: %d\n", max);
    } else {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (findMax(arr3, (int)(sizeof(arr3) / sizeof(arr3[0])), &max) == 0) {
        printf("Maximum: %d\n", max);
    } else {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (findMax(arr4, (int)(sizeof(arr4) / sizeof(arr4[0])), &max) == 0) {
        printf("Maximum: %d\n", max);
    } else {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (findMax(NULL, 0, &max) != 0) {
        printf("Handled invalid input correctly\n");
    }

    return EXIT_SUCCESS;
}