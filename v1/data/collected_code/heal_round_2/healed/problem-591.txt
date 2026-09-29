#include <stdio.h>

void interchangeElements(int arr[], int size) {
    int temp = arr[0];
    arr[0] = arr[size - 1];
    arr[size - 1] = temp;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    
    printf("Before interchange: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    interchangeElements(arr, size);
    
    printf("After interchange: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    return 0;
}