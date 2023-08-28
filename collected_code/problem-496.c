#include <stdio.h>
#include <stdlib.h>

void heapify(int *arr, int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
  
    if (left < n && arr[left] < arr[smallest])
        smallest = left;
  
    if (right < n && arr[right] < arr[smallest])
        smallest = right;
  
    if (smallest != i) {
        int temp = arr[i];
        arr[i] = arr[smallest];
        arr[smallest] = temp;
        heapify(arr, n, smallest);
    }
}

void buildHeap(int *arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
}

void findSmallestIntegers(int *arr, int n, int k) {
    buildHeap(arr, n);

    for (int i = 0; i < k; i++) {
        int smallest = arr[0];
        arr[0] = arr[n - 1];
        arr[n - 1] = smallest;
        n--;
        heapify(arr, n, 0);
    }
}

int main() {
    int arr[] = {4, 7, 2, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 3;
  
    findSmallestIntegers(arr, n, k);
  
    printf("Smallest %d integers: ", k);
    for (int i = 0; i < k; i++)
        printf("%d ", arr[n - k + i]);

    return 0;
}