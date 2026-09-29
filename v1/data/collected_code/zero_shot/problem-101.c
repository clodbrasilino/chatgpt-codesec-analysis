#include<stdio.h>

int findKthElement(int arr[], int size, int k) {
    // Sort the array in ascending order
    for (int i = 0; i < size-1; i++) {
        for (int j = 0; j < size-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
    
    // Return the kth element
    return arr[k-1];
}

int main() {
    int arr[] = {9, 4, 2, 7, 1};
    int size = sizeof(arr) / sizeof(arr[0]);
    int k = 3;
    
    int kthElement = findKthElement(arr, size, k);
    
    printf("The %dth element in the array is: %d\n", k, kthElement);
    
    return 0;
}