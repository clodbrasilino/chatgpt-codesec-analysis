#include <stdio.h>
#include <stdlib.h>

int find_min(const int arr[], int n) {
    if (n <= 0) {
        return -1;
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
    return arr[low];
}

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
        arr[i] = atoi(argv[i + 1]);
    }
    int min_val = find_min(arr, n);
    printf("%d\n", min_val);
    free(arr);
    return 0;
}