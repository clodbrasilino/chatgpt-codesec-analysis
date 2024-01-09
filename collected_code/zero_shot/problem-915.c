#include <stdio.h>

void rearrangeArray(int arr[], int n) {
    int i, j = 0, temp;
    
    for (i = 0; i < n; i++) {
        if (arr[i] < 0) {
            if (i != j) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
            j++;
        }
    }
}

int main() {
    int arr[] = {-1, 3, -2, 4, 5, -6, 7, -8, 9};
    int n = sizeof(arr)/sizeof(arr[0]);
    
    rearrangeArray(arr, n);
    
    printf("Rearranged array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    
    return 0;
}