#include <stdio.h>
#include <stdbool.h>

bool canBeSorted(int arr[], int n) {
    int i;
    for (i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            if (i != 0 && i != n - 2 && arr[i - 1] > arr[i + 1] && arr[i] > arr[i + 2]) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    if (canBeSorted(arr, n)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
    return 0;
}