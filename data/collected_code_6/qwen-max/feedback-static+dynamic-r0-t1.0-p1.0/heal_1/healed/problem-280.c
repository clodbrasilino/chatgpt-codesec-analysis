#include <stdio.h>
#include <stdbool.h>

bool sequential_search(const int arr[], int n, int target) {
    for (int i = 0; i < n; ++i) {
        if (arr[i] == target) {
            return true;
        }
    }
    return false;
}

int main() {
    const int arr[] = {3, 5, 7, 9, 11};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 7;

    if (sequential_search(arr, n, target)) {
        printf("Element found\n");
    } else {
        printf("Element not found\n");
    }

    return 0;
}