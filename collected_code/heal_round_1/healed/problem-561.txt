#include <stdio.h>

void assignPairs(int arr[], int n) {
    if (n < 2) {
        printf("Please provide valid array size\n");
        return;
    }
    for (int i = 0; i < n - 1; i += 2) {
        arr[i + 1] = arr[i];
    }
}

int main() {
    int arr[] = {5, 2, 8, 7, 4, 1, 3};
    int n = sizeof(arr) / sizeof(arr[0]);

    assignPairs(arr, n);

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}