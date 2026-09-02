#include <stdio.h>

void rearrange(int arr[], int n) {
    int i = 0, j = n - 1;
    
    while (i < j) {
        while (i < n && arr[i] >= 0) {
            i++;
        }
        while (j >= 0 && arr[j] < 0) {
            j--;
        }
        if (i < j) {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    
    int pos = 0, neg = 1;
    while (pos < n && arr[pos] < 0) {
        pos++;
    }
    while (neg < n && arr[neg] >= 0) {
        neg++;
    }
    
    while (pos < n && neg < n) {
        int temp = arr[pos];
        arr[pos] = arr[neg];
        arr[neg] = temp;
        pos += 2;
        neg += 2;
    }
}

int main(void) {
    int arr[] = {1, -2, 3, -4, 5, -6, 7, -8};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    rearrange(arr, n);
    
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    return 0;
}