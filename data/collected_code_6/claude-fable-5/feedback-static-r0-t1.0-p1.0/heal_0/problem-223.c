#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static int firstOccurrence(const int arr[], int n, int target)
{
    int low = 0;
    int high = n - 1;
    int result = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) {
            result = mid;
            high = mid - 1;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return result;
}

static bool isMajority(const int arr[], int n, int candidate)
{
    if (arr == NULL || n <= 0) {
        return false;
    }

    int first = firstOccurrence(arr, n, candidate);
    if (first == -1) {
        return false;
    }

    int lastPossible = first + n / 2;
    if (lastPossible < n && arr[lastPossible] == candidate) {
        return true;
    }
    return false;
}

int main(void)
{
    int arr1[] = {1, 2, 3, 3, 3, 3, 10};
    int n1 = (int)(sizeof(arr1) / sizeof(arr1[0]));
    int candidate1 = 3;

    int arr2[] = {1, 1, 2, 4, 4, 4, 6, 6};
    int n2 = (int)(sizeof(arr2) / sizeof(arr2[0]));
    int candidate2 = 4;

    if (isMajority(arr1, n1, candidate1)) {
        if (printf("%d is the majority element in array 1\n", candidate1) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("%d is not the majority element in array 1\n", candidate1) < 0) {
            return EXIT_FAILURE;
        }
    }

    if (isMajority(arr2, n2, candidate2)) {
        if (printf("%d is the majority element in array 2\n", candidate2) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("%d is not the majority element in array 2\n", candidate2) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}