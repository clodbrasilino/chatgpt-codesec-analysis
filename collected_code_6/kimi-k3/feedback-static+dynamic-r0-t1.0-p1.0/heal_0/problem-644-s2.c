#include <stdio.h>

void reverse_array(int arr[], int size, int pos) {
    if (arr == NULL || size <= 0 || pos < 0 || pos >= size) {
        return;
    }
    
    int start = 0;
    int end = pos;
    
    while (start < end) {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

void print_array(const int arr[], int size) {
    if (arr == NULL || size <= 0) {
        return;
    }
    
    int i;
    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void) {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(arr) / sizeof(arr[0]);
    int pos = 5;
    
    printf("Original array: ");
    print_array(arr, size);
    
    reverse_array(arr, size, pos);
    
    printf("Array after reversing up to position %d: ", pos);
    print_array(arr, size);
    
    return 0;
}