#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int count_rotations(const int *arr, int n) {
    if (arr == NULL || n <= 0) {
        return -1;
    }

    int low = 0;
    int high = n - 1;

    while (low <= high) {
        if (arr[low] <= arr[high]) {
            return low;
        }

        int mid = low + (high - low) / 2;
        int prev = (mid - 1 + n) % n;
        int next = (mid + 1) % n;

        if (arr[mid] <= arr[prev] && arr[mid] <= arr[next]) {
            return mid;
        }

        if (arr[mid] <= arr[high]) {
            if (arr[mid] == arr[high]) {
                high--;
            } else {
                high = mid - 1;
            }
        } else if (arr[low] <= arr[mid]) {
            if (arr[low] == arr[mid]) {
                low++;
            } else {
                low = mid + 1;
            }
        } else {
            high = mid - 1;
        }
    }

    return 0;
}

int main(int argc, char * const argv[]) {
    if (argc < 2) {
        return 1;
    }

    int n = argc - 1;
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        char *endptr;
        long val = strtol(argv[i + 1], &endptr, 10);
        if (val > INT_MAX || val < INT_MIN || *endptr != '\0') {
            free(arr);
            return 1;
        }
        arr[i] = (int)val;
    }

    int rotations = count_rotations(arr, n);
    if (rotations >= 0) {
        printf("%d\n", rotations);
    }

    free(arr);

    return 0;
}