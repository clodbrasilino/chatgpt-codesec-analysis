#include <stdio.h>
#include <stdlib.h>

#define HEAP_SIZE 3

void swap(int *a, int *b) {
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

void buildHeap(int arr[], int n) {
    int startIdx = (n / 2) - 1;

    for (int i = startIdx; i >= 0; i--) {
        heapify(arr, n, i);
    }
}

int maximumProduct(int* nums, int numsSize){
    int heap[HEAP_SIZE] = {0};
    for(int i = 0; i < numsSize; i++) {
        if(i < HEAP_SIZE) {
            heap[i] = nums[i];
            if(i == HEAP_SIZE - 1) {
                buildHeap(heap, HEAP_SIZE);
            }
        } else {
            if(nums[i] > heap[0]) {
                heap[0] = nums[i];
                heapify(heap, HEAP_SIZE, 0);
            }
        }
    }
    return heap[0] * heap[1] * heap[2];
}

int main() {
    int arr[] = {1, 20, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Maximum product is %d\n", maximumProduct(arr, n));
    return 0;
}