#include <stdio.h>
#include <stdlib.h>

int find_last_removed(int arr[], int size, int removed[], int removed_size) {
    if (arr == NULL || removed == NULL || size <= 0 || removed_size <= 0) {
        return -1;
    }
    
    int last_removed = removed[removed_size - 1];
    
    for (int i = 0; i < size; i++) {
        if (arr[i] == last_removed) {
            return i;
        }
    }
    
    return -1;
}

int main(void) {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(arr) / sizeof(arr[0]);
    int removed[] = {3, 7, 5};
    int removed_size = sizeof(removed) / sizeof(removed[0]);
    
    int position = find_last_removed(arr, size, removed, removed_size);
    
    if (position != -1) {
        printf("Position of last removed element: %d\n", position);
    } else {
        printf("Last removed element not found in array\n");
    }
    
    return 0;
}