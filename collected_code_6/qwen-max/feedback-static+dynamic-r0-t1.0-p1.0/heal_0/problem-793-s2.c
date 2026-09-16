#include <stdio.h>
#include <stdlib.h>

int find_last_position(int *arr, int n, int x) {
    int low = 0, high = n - 1, result = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == x) {
            result = mid;
            low = mid + 1;
        } else if (arr[mid] < x) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return result;
}

int main() {
    int arr[] = {1, 2, 2, 3, 4, 4, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 4;
    int index = find_last_position(arr, n, x);
    printf("Last position of %d in array is %d\n", x, index);
    return 0;
}