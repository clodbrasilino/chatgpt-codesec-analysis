#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 3, got <no output>
  *  test case 1 failed: expected 2, got <no output>
  *  test case 0 failed: expected 1, got <no output>
  */

int countRotations(const int* arr, int n) {
    if (arr == NULL || n <= 0) {
        return -1;
    }

    int left = 0;
    int right = n - 1;

    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] > arr[right]) {
            left = mid + 1;
        } else if (arr[mid] < arr[right]) {
            right = mid;
        } else {
            right--;
        }
    }

    return left;
}

int main(void) {
    int n;
    if (scanf("%d", &n) == 1) {
        int* arr = (int*)malloc(n * sizeof(int));
        if (arr) {
            for (int i = 0; i < n; i++) {
                if (scanf("%d", &arr[i]) != 1) {
                    break;
                }
            }

            int rotations = countRotations(arr, n);

            if (rotations != -1) {
                printf("%d\n", rotations);
            }

            free(arr);
        }
    }
    return 0;
}