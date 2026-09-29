#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int minJumps(const int *arr, size_t n)
{
    size_t jumps;
    size_t currentEnd;
    size_t farthest;
    size_t i;

    if (arr == NULL || n == 0U) {
        return -1;
    }

    if (n == 1U) {
        return 0;
    }

    jumps = 0U;
    currentEnd = 0U;
    farthest = 0U;

    for (i = 0U; i < (n - 1U); i++) {
        if (arr[i] < 0) {
            return -1;
        }

        if ((i + (size_t)arr[i]) > farthest) {
            farthest = i + (size_t)arr[i];
        }

        if (i == currentEnd) {
            if (farthest == i) {
                return -1;
            }
            jumps++;
            currentEnd = farthest;
            if (currentEnd >= (n - 1U)) {
                break;
            }
        }
    }

    if (currentEnd < (n - 1U)) {
        return -1;
    }

    if (jumps > (size_t)INT_MAX) {
        return -1;
    }

    return (int)jumps;
}

int main(void)
{
    int arr1[] = {1, 3, 5, 8, 9, 2, 6, 7, 6, 8, 9};
    int arr2[] = {1, 1, 1, 1, 1};
    int arr3[] = {2, 3, 1, 1, 4};
    int arr4[] = {1, 0, 3, 4};
    int result;

    result = minJumps(arr1, sizeof(arr1) / sizeof(arr1[0]));
    if (result >= 0) {
        if (printf("Minimum jumps for arr1: %d\n", result) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("arr1: end not reachable\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    result = minJumps(arr2, sizeof(arr2) / sizeof(arr2[0]));
    if (result >= 0) {
        if (printf("Minimum jumps for arr2: %d\n", result) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("arr2: end not reachable\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    result = minJumps(arr3, sizeof(arr3) / sizeof(arr3[0]));
    if (result >= 0) {
        if (printf("Minimum jumps for arr3: %d\n", result) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("arr3: end not reachable\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    result = minJumps(arr4, sizeof(arr4) / sizeof(arr4[0]));
    if (result >= 0) {
        if (printf("Minimum jumps for arr4: %d\n", result) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("arr4: end not reachable\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}