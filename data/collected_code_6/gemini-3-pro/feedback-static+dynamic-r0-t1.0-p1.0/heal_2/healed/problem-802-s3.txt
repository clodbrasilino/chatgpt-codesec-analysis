#include <stdio.h>
#include <stdlib.h>

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
        } else {
            right = mid;
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