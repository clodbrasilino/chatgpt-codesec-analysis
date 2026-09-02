#include <stdio.h>
#include <stdbool.h>

bool hasDuplicate(const int *arr, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] == arr[j]) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 2};
    int n = sizeof(arr) / sizeof(arr[0]);

    if (hasDuplicate(arr, n)) {
        printf("Array contains duplicates.\n");
    } else {
        printf("Array does not contain duplicates.\n");
    }

    return 0;
}