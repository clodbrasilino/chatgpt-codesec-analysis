#include <stdio.h>
#include <stdbool.h>

bool isMinHeap(const int arr[], size_t size) {
    if (arr == NULL || size == 0) {
        return false;
    }
    
    for (size_t i = 0; i <= (size - 2) / 2; i++) {
        size_t left = 2 * i + 1;
        size_t right = 2 * i + 2;
        
        if (left < size && arr[i] > arr[left]) {
            return false;
        }
        if (right < size && arr[i] > arr[right]) {
            return false;
        }
    }
    return true;
}

int main(void) {
    int heap[] = {1, 3, 5, 7, 9, 11};
    size_t size = sizeof(heap) / sizeof(heap[0]);
    
    if (isMinHeap(heap, size)) {
        printf("Array is a min heap\n");
    } else {
        printf("Array is not a min heap\n");
    }
    
    return 0;
}