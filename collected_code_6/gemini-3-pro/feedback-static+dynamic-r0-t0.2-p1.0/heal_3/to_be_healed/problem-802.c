#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 2, got 3
  *  test case 2 failed: expected 3, got 5
  */

int countRotations(const int arr[], int n) {
    if (n <= 0) {
        return 0;
    }

    int low = 0;
    int high = n - 1;

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
            printf("%d\n", countRotations(arr, n));
            free(arr);
        }
    }
    return 0;
}