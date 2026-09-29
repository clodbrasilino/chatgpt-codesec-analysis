#include <stdio.h>
#include <stdlib.h>

int is_majority(const int arr[], int n, int x) {
    if (arr == NULL || n <= 0) {
        return 0;
    }

    int low = 0;
    int high = n - 1;
    int first_index = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == x) {
            first_index = mid;
            high = mid - 1;
        } else if (arr[mid] < x) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    if (first_index == -1) {
        return 0;
    }

    if ((first_index + n / 2) < n && arr[first_index + n / 2] == x) {
        return 1;
    }

    return 0;
}

int main() {
    int arr[] = {1, 2, 3, 3, 3, 3, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 3;

    if (is_majority(arr, n, x)) {
        printf("%d is the majority element\n", x);
    } else {
        printf("%d is not the majority element\n", x);
    }

    return 0;
}