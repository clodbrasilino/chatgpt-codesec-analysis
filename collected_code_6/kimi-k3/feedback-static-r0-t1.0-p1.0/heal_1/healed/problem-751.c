#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool is_min_heap(const int arr[], size_t n) {
    if (arr == NULL) {
        return false;
    }
    
    if (n <= 1) {
        return true;
    }
    
    for (size_t i = 0; i <= (n - 2) / 2; i++) {
        size_t left = 2 * i + 1;
        size_t right = 2 * i + 2;
        
        if (left < n && arr[i] > arr[left]) {
            return false;
        }
        
        if (right < n && arr[i] > arr[right]) {
            return false;
        }
    }
    
    return true;
}

int main(void) {
    int heap[] = {1, 3, 5, 7, 9, 11};
    size_t heap_size = sizeof(heap) / sizeof(heap[0]);
    
    int not_heap[] = {1, 5, 3, 7, 9, 11};
    size_t not_heap_size = sizeof(not_heap) / sizeof(not_heap[0]);
    
    int empty[] = {0};
    size_t empty_size = 0;
    
    printf("Test 1 (valid min heap): %s\n", 
           is_min_heap(heap, heap_size) ? "true" : "false");
    
    printf("Test 2 (invalid min heap): %s\n", 
           is_min_heap(not_heap, not_heap_size) ? "true" : "false");
    
    printf("Test 3 (empty array): %s\n", 
           is_min_heap(empty, empty_size) ? "true" : "false");
    
    printf("Test 4 (NULL array): %s\n", 
           "false");
    
    return EXIT_SUCCESS;
}