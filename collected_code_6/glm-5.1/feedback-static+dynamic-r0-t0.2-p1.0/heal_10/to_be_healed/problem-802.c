#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int count_rotations(const int *arr, int n) {
    if (arr == NULL || n <= 0) {
        return -1;
    }

    int low = 0;
    int high = n - 1;

    while (arr[low] > arr[high]) {
        if (high - low == 1) {
            return high;
        }

        int mid = low + (high - low) / 2;

        if (arr[mid] <= arr[high] && arr[mid] <= arr[low]) {
            int min_idx = low;
            for (int i = low + 1; i <= high; i++) {
                if (arr[i] < arr[min_idx]) {
                    min_idx = i;
                }
            }
            return min_idx;
        }

        if (arr[mid] >= arr[low]) {
            low = mid;
        } else {
            high = mid;
        }
    }

    return low;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
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