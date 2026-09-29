#include <stdbool.h>
#include <stdio.h>

bool canBeSorted(int arr[], int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (arr[i] > arr[j]) {
                if (j != i + 1 && j != n - 1 && i != 0) {
                    return false;
                }
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