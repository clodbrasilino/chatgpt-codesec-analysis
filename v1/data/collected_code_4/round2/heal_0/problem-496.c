#include <stdio.h>
#include <stdlib.h>

#define HEAP_SIZE 128

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int arr[], int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] < arr[smallest])
        smallest = left;
 
    if (right < n && arr[right] < arr[smallest])
        smallest = right;
  
    if (smallest != i) {
        swap(&arr[i], &arr[smallest]);
        heapify(arr, n, smallest);
    }
}

void build_min_heap(int arr[], int n) {
    int startIdx = (n / 2) - 1;
 
    for (int i = startIdx; i >= 0; i--){
        heapify(arr, n, i);
    }
}

int find_minimum(int arr[], int n) {
    build_min_heap(arr, n);
    return arr[0];
}

int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int size = sizeof(arr) / sizeof(arr[0]);

    int min = find_minimum(arr, size);

    printf("The smallest number in the list is: %d\n", min);

    return 0;
}