#include <stdio.h>

void filterOdd(int arr[], int n) {
    printf("Odd numbers: ");
    
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 != 0) {
            printf("%d ", arr[i]);
        }
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    filterOdd(arr, n);
    
    return 0;
}