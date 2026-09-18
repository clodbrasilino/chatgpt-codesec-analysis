#include <stdio.h>
#include <stdlib.h>

int countRotations(const int arr[], int n) {
    int low = 0, high = n - 1;
    
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] > arr[high]) {
            low = mid + 1;
        } else if (arr[mid] < arr[high]) {
            high = mid;
        } else {
            high--;
        }
    }
    return low;
}

int main(void) {
    int n;
    if (scanf("%d", &n) == 1) {
        int *arr = (int *)malloc(n * sizeof(int));
        if (arr) {
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