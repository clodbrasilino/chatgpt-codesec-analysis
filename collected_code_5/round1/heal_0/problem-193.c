#include <stdio.h>

void remove_duplicates(int* arr, int* size) {
    int i, j, k;
    for (i = 0; i < *size; ++i) {
        for (j = i + 1; j < *size;) {
            if (arr[i] == arr[j]) {
                for (k = j; k < *size; ++k) {
                    arr[k] = arr[k + 1];
                }
                --*size;
            } else {
                ++j;
            }
        }
    }
}

int main() {
    int arr[] = {10, 20, 30, 20, 40, 10, 50};
    int n = sizeof(arr) / sizeof(arr[0]);
    remove_duplicates(arr, &n);

    int i;
    for (i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    return 0;
}