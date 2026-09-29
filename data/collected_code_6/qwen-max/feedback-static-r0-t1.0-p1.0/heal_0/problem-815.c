#include <stdio.h>
#include <stdlib.h>

void sortArray(int *arr, int n) {
    int count[3] = {0, 0, 0};
    for (int i = 0; i < n; i++) {
        count[arr[i]]++;
    }
    int k = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < count[i]; j++) {
            arr[k++] = i;
        }
    }
}

int main() {
    int arr[] = {2, 0, 1, 2, 0, 1, 0, 1, 2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    sortArray(arr, n);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    return 0;
}