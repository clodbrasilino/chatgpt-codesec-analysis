#include <stdio.h>
#include <stdlib.h>

void reverse_array(int *arr, int n, int pos) {
    if (pos >= 0 && pos < n) {
        for (int i = 0; i < pos / 2; i++) {
            int temp = arr[i];
            arr[i] = arr[pos - i - 1];
            arr[pos - i - 1] = temp;
        }
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int pos = 3;

    reverse_array(arr, n, pos);

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}