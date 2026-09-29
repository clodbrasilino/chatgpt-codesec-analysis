#include <stdio.h>
#include <stdlib.h>

void maxHeapify(int *arr, int n, int i) {
    int largest = i; 
    int left = 2*i + 1;  
    int right = 2*i + 2; 

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        int swap = arr[i];
        arr[i] = arr[largest];
        arr[largest] = swap;
        
        maxHeapify(arr, n, largest);
    }
}

void buildMaxHeap(int *arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        maxHeapify(arr, n, i);
}

int extractMax(int *arr, int n) {
    if (n <= 0) return -1; // Invalid case
    if (n == 1) {
        n--;
        return arr[0];
    }

    int root = arr[0];
    arr[0] = arr[n-1];
    n--;
    maxHeapify(arr, n, 0);

    return root;
}

int main() {
    int numbers[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(numbers)/sizeof(numbers[0]);
    
    buildMaxHeap(numbers, n);
    
    printf("Largest element: %d\n", extractMax(numbers, n));
    
    free(NULL); // No need to free static array
    
    return 0;
}