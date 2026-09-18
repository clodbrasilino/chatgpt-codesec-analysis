#include <stdio.h>
#include <stdlib.h>

int countRotations(const int arr[], int n) {
    if (n <= 0) {
        return 0;
    }

    int low = 0;
    int high = n - 1;

    while (low <= high) {
        if (arr[low] <= arr[high]) {
            return low;
        }

        int mid = low + (high - low) / 2;
        int next = (mid + 1) % n;
        int prev = (mid + n - 1) % n;

        if (arr[mid] <= arr[next] && arr[mid] <= arr[prev]) {
            return mid;
        }

        if (arr[mid] <= arr[high]) {
            high = mid - 1;
        } else if (arr[mid] >= arr[low]) {
            low = mid + 1;
        }
    }

    return 0;
}

int main(void) {
    int n;
    
    if (scanf("%d", &n) == 1 && n > 0) {
        int *arr = (int *)malloc(n * sizeof(int));
        if (arr != NULL) {
            for (int i = 0; i < n; i++) {
                scanf("%d", &arr[i]);
            }
            
            int rotations = countRotations(arr, n);
            printf("%d\n", rotations);
            
            free(arr);
        }
    }

    return 0;
}