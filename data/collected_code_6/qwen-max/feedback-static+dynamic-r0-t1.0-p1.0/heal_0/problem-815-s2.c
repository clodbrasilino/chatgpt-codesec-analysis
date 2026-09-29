#include <stdio.h>
#include <stdlib.h>

void sortArray(int* arr, int n) {
    int count[3] = {0};
    for (int i = 0; i < n; ++i) {
        count[arr[i]]++;
    }
    int index = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < count[i]; ++j) {
            arr[index++] = i;
        }
    }
}

int main() {
    int arr[] = {2, 0, 1, 2, 1, 0};
    int n = sizeof(arr) / sizeof(arr[0]);
    sortArray(arr, n);
    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    return 0;
}