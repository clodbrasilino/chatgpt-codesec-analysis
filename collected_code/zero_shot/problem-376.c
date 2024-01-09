#include <stdio.h>

void removeDuplicates(int arr[], int n, int customValue) {
    int i, j, k;

    for (i = 0; i < n; i++) {
        for (j = i+1; j < n; j++) {
            if (arr[i] == arr[j]) {
                for (k = j; k < n-1; k++) {
                    arr[k] = arr[k+1];
                }
                n--;
                arr[n] = customValue;
                j--;
            }
        }
    }
}

int main() {
    int arr[] = {1, 2, 2, 3, 4, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int customValue = -1;

    removeDuplicates(arr, n, customValue);

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}