#include <stdio.h>
#include <stdlib.h>

void reverseArrayUptoPosition(int *arr, int size, int position) {
    if (arr == NULL || size <= 0 || position < 0 || position >= size) {
        return;
    }
    
    int left = 0;
    int right = position;
    
    while (left < right) {
        int temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;
        left++;
        right--;
    }
}

void printArray(const int *arr, int size) {
    if (arr == NULL || size <= 0) {
        return;
    }
    
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void) {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(arr) / sizeof(arr[0]);
    int position = 4;
    
    printf("Original array: ");
    printArray(arr, size);
    
    reverseArrayUptoPosition(arr, size, position);
    
    printf("Array after reversing up to position %d: ", position);
    printArray(arr, size);
    
    return EXIT_SUCCESS;
}