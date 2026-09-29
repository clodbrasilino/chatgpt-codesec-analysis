#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 3, got 5
  *  test case 1 failed: expected 2, got 3
  */

long count_rotations(const int *arr, size_t n) {
    if (arr == NULL || n == 0) {
        return -1;
    }

    size_t low = 0;
    size_t high = n - 1;

    while (low < high) {
        size_t mid = low + (high - low) / 2;

        if (arr[mid] > arr[high]) {
            low = mid + 1;
        } else if (arr[mid] < arr[high]) {
            high = mid;
        } else {
            high--;
        }
    }

    return (long)low;
}

int main(void) {
    size_t n;
    while (scanf("%zu", &n) == 1) {
        if (n == 0) {
            /* Possible weaknesses found:
             *  Assignment 'result=count_rotations(NULL,0)', assigned value is -1
             *  Calling function 'count_rotations' returns -1
             */
            long result = count_rotations(NULL, 0);
            /* Possible weaknesses found:
             *  Condition 'result!=-1' is always false [knownConditionTrueFalse]
             *  Condition 'result!=-1' is always false
             */
            if (result != -1) {
                printf("%ld\n", result);
            }
            continue;
        }

        int *arr = (int *)malloc(n * sizeof(int));
        if (arr == NULL) {
            return 1;
        }

        for (size_t i = 0; i < n; i++) {
            if (scanf("%d", &arr[i]) != 1) {
                free(arr);
                return 1;
            }
        }

        long result = count_rotations(arr, n);
        if (result != -1) {
            printf("%ld\n", result);
        }

        free(arr);
    }

    return 0;
}