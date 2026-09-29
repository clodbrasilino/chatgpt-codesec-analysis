#include <stdio.h>

void moveZeroesToEnd(int *arr, int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] != 0) {
            arr[count++] = arr[i];
        }
    }
    while (count < n) {
        arr[count++] = 0;
    }
}

int main() {
    int n;
    printf("Enter the size of array: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter the elements of array: ");

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    moveZeroesToEnd(arr, n);
    
    printf("New array with zeroes moved to the end: ");
    
    for(int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    
    return 0;
}