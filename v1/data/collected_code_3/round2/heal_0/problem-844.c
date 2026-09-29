#include <stdio.h>

int findKthElement(int arr[], int n, int k) {
    int odd[n], even[n], i, j = 0, l = 0;
    for (i = 0; i < n; i++) {
        if (arr[i] % 2 != 0) {
            odd[j++] = arr[i];
        } else {
            even[l++] = arr[i];
        }
    }
    for (i = 0; i < j; i++) {
        arr[i] = odd[i];
    }
    for (i = 0; i < l; i++) {
        arr[i + j] = even[i];
    }
    return arr[k - 1];
}

int main() {
    int arr[] = {1, 3, 2, 4, 7, 6, 5, 8, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 3;
    printf("The %dth element is %d", k, findKthElement(arr, n, k));
    return 0;
}