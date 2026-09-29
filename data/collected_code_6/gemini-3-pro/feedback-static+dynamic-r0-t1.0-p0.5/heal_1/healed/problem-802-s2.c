#include <stdio.h>
#include <stdlib.h>

int countRotations(const int arr[], int n) {
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

    return -1;
}

int main(void) {
    int capacity = 100;
    int n = 0;
    int *arr = (int *)malloc(capacity * sizeof(int));
    
    if (arr == NULL) {
        return 1;
    }

    int temp;
    while (scanf("%d", &temp) == 1) {
        arr[n++] = temp;
        if (n >= capacity) {
            capacity *= 2;
            int *new_arr = (int *)realloc(arr, capacity * sizeof(int));
            if (new_arr == NULL) {
                free(arr);
                return 1;
            }
            arr = new_arr;
        }
    }

    if (n > 0) {
        int rotations = countRotations(arr, n);
        if (rotations != -1) {
            printf("%d\n", rotations);
        } else {
            printf("Error\n");
        }
    }

    free(arr);
    return 0;
}