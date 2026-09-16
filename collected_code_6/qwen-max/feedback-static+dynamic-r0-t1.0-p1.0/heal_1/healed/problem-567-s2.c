#include <stdio.h>
#include <stdbool.h>

bool is_sorted(const int *arr, int n) {
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[i - 1]) {
            return false;
        }
    }
    return true;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    if (is_sorted(arr, n)) {
        printf("Array is sorted.\n");
    } else {
        printf("Array is not sorted.\n");
    }

    return 0;
}