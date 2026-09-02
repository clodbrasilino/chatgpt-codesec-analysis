#include <stdio.h>
#include <stdbool.h>

bool sequential_search(const int arr[], int n, int target) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            return true;
        }
    }
    return false;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 5;

    if (sequential_search(arr, n, target)) {
        printf("Element found\n");
    } else {
        printf("Element not found\n");
    }

    return 0;
}