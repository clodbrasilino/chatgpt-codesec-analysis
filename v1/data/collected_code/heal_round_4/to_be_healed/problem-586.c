#include <stdio.h>

void splitAndAdd(int arr[], int n, int k) {
    if (k > n) {
        return;
    }
    
    int temp[k];

    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    for (int i = 0; i < k; i++) {
        temp[i] = arr[i];
    }
    
    for (int i = 0; i < n - k; i++) {
        arr[i] = arr[i + k];
    }
    
    for (int i = n - k, j = 0; i < n; i++, j++) {
        arr[i] = temp[j];
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 2;
    
    if (k > 0 && k <= n) {
        splitAndAdd(arr, n, k);
    }
    
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    
    return 0;
}