#include <stdio.h>

void swap(int *a, int *b) {
    int temp = 0;
    
    if (a && b) {
        temp = *a;
        *a = *b;
        *b = temp;
    }
}

void exchangePositions(int arr[], int size, int n) {
    if (arr && size > 0 && n > 0) {
        for (int i = 0; i < size - 1; i++) {
            if (i % n == n - 1) {
                swap(&arr[i], &arr[i + 1]);
                i++;
            }
        }
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6};
    int size = sizeof(arr) / sizeof(arr[0]);
    int n = 3;
    
    exchangePositions(arr, size, n);
    
    printf("Modified array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    
    return 0;
}