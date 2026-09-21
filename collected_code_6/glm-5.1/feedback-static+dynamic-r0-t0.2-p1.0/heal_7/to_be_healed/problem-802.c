#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 2, got 3
  *  test case 2 failed: expected 3, got 5
  */

int count_rotations(const int *arr, int n) {
    if (arr == NULL || n <= 0) {
        return -1;
    }

    int low = 0;
    int high = n - 1;

    while (arr[low] >= arr[high]) {
        if (low == high) {
            return low;
        }

        int mid = low + (high - low) / 2;

        if (arr[mid] == arr[high]) {
            if (arr[high - 1] > arr[high]) {
                return high;
            }
            high--;
            continue;
        }

        if (arr[mid] > arr[high]) {
            low = mid + 1;
        } else {
            if (mid > 0 && arr[mid - 1] > arr[mid]) {
                return mid;
            }
            high = mid - 1;
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