#include <stdio.h>
#include <stdlib.h>

int find_last_removed_position(const int *arr, int size, const int *removed_order) {
    if (arr == NULL || removed_order == NULL || size <= 0) {
        return -1;
    }
    
    int *positions = (int *)malloc(size * sizeof(int));
    if (positions == NULL) {
        return -1;
    }
    
    for (int i = 0; i < size; i++) {
        positions[i] = i;
    }
    
    int remaining = size;
    int last_position = -1;
    
    for (int i = 0; i < size; i++) {
        int idx_to_remove = removed_order[i];
        if (idx_to_remove < 0 || idx_to_remove >= remaining) {
            free(positions);
            return -1;
        }
        
        last_position = positions[idx_to_remove];
        
        for (int j = idx_to_remove; j < remaining - 1; j++) {
            positions[j] = positions[j + 1];
        }
        remaining--;
    }
    
    free(positions);
    return last_position;
}

int main(void) {
    int arr[] = {10, 20, 30, 40, 50};
    int size = sizeof(arr) / sizeof(arr[0]);
    /* Possible weaknesses found:
     *  Variable 'removed_order' can be declared as const array [constVariable]
     */
    int removed_order[] = {1, 2, 0, 1, 0};
    
    int result = find_last_removed_position(arr, size, removed_order);
    
    if (result != -1) {
        printf("Last removed element position: %d\n", result);
        printf("Last removed element value: %d\n", arr[result]);
    } else {
        printf("Invalid input or error occurred\n");
    }
    
    return 0;
}