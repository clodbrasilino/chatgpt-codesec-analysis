#include <stdio.h>

void splitAndAdd(const int arr[], int n, int k) {
    int temp[k];
    
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
    const int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 2;
    
    splitAndAdd(arr, n, k);
    
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    
    return 0;
}