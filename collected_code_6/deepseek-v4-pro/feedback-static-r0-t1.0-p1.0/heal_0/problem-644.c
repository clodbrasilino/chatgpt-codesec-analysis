#include <stdio.h>

void reverseArrayUptoPosition(int arr[], int pos, int size) {
    if (pos > size || pos <= 0) {
        printf("Invalid position\n");
        return;
    }
    
    int start = 0;
    int end = pos - 1;
    
    while (start < end) {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(arr) / sizeof(arr[0]);
    int pos = 5;
    
    printf("Original array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    reverseArrayUptoPosition(arr, pos, size);
    
    printf("Array after reversing upto position %d: ", pos);
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    return 0;
}