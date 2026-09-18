#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 3, got 5
  *  test case 1 failed: expected 2, got 3
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
    int capacity = 16;
    int *arr = (int *)malloc(capacity * sizeof(int));
    int n = 0;
    
    if (arr == NULL) {
        return 1;
    }

    while (scanf("%d", &arr[n]) == 1) {
        n++;
        if (n >= capacity) {
            capacity *= 2;
            int *temp = (int *)realloc(arr, capacity * sizeof(int));
            if (temp == NULL) {
                free(arr);
                return 1;
            }
            arr = temp;
        }
    }
    
    if (n > 0) {
        int rotations = countRotations(arr, n);
        printf("%d\n", rotations);
    }
    
    free(arr);
    return 0;
}