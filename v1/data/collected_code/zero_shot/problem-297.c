#include<stdio.h>

void flatten(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == -1) {
            printf("\n");
        } else {
            printf("%d ", arr[i]);
        }
    }
}

int main() {
    int arr[] = {1, 2, -1, 3, -1, 4, 5, 6, -1, -1, 7, -1};
    int n = sizeof(arr) / sizeof(arr[0]);
    flatten(arr, n);
    return 0;
}