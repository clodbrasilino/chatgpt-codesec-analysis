#include <stdio.h>
#include <stdlib.h>

void rearrange(int *arr, int n) {
    int left = 0, right = n - 1;
    while (left < right) {
        while (left < right && arr[left] < 0) left++;
        while (left < right && arr[right] >= 0) right--;
        if (left < right) {
            int temp = arr[left];
            arr[left] = arr[right];
            arr[right] = temp;
        }
    }
}

int main() {
    int arr[] = {-12, 11, -13, -5, 6, -7, 5, -3, 11};
    int n = sizeof(arr) / sizeof(arr[0]);
    rearrange(arr, n);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    return 0;
}