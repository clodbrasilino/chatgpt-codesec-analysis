#include <stdio.h>
#include <stdlib.h>

void split_and_add(int *arr, int n, int k) {
    if (k > 0 && k < n) {
        int *temp = (int *)malloc(k * sizeof(int));
        if (temp == NULL) {
            return;
        }
        for (int i = 0; i < k; ++i) {
            temp[i] = arr[i];
        }
        for (int i = 0; i < n - k; ++i) {
            arr[i] = arr[k + i];
        }
        for (int i = 0; i < k; ++i) {
            arr[n - k + i] = temp[i];
        }
        free(temp);
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = 5;
    int k = 2;

    split_and_add(arr, n, k);

    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }

    return 0;
}