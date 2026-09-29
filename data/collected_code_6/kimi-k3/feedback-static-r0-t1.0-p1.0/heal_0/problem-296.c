#include <stdio.h>
#include <stdlib.h>

long long mergeAndCount(int arr[], int temp[], int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;
    long long invCount = 0;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            invCount += (mid - i + 1);
        }
    }

    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    while (j <= right) {
        temp[k++] = arr[j++];
    }

    for (i = left; i <= right; i++) {
        arr[i] = temp[i];
    }

    return invCount;
}

long long mergeSortAndCount(int arr[], int temp[], int left, int right) {
    long long invCount = 0;
    if (left < right) {
        int mid = left + (right - left) / 2;
        invCount += mergeSortAndCount(arr, temp, left, mid);
        invCount += mergeSortAndCount(arr, temp, mid + 1, right);
        invCount += mergeAndCount(arr, temp, left, mid, right);
    }
    return invCount;
}

long long countInversions(int arr[], int n) {
    if (arr == NULL || n <= 0) {
        return 0;
    }

    int *temp = (int *)malloc(n * sizeof(int));
    if (temp == NULL) {
        return -1;
    }

    long long result = mergeSortAndCount(arr, temp, 0, n - 1);
    free(temp);
    return result;
}

int main(void) {
    int arr[] = {8, 4, 2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    long long inversions = countInversions(arr, n);
    if (inversions >= 0) {
        printf("Number of inversions: %lld\n", inversions);
    } else {
        printf("Memory allocation failed\n");
        return 1;
    }

    return 0;
}