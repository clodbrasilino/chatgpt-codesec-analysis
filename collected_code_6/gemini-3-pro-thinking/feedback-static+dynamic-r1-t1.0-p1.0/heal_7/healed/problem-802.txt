#include <stdio.h>
#include <stddef.h>

size_t count_rotations(const int *arr, size_t n) {
    if (!arr || n == 0) {
        return 0;
    }

    size_t low = 0;
    size_t high = n - 1;

    while (low < high) {
        if (arr[low] < arr[high]) {
            break;
        }

        size_t mid = low + (high - low) / 2;

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
    size_t n;
    
    while (scanf("%zu", &n) == 1) {
        int arr[n];
        for (size_t i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }
        
        printf("%zu\n", count_rotations(arr, n));
    }

    return 0;
}