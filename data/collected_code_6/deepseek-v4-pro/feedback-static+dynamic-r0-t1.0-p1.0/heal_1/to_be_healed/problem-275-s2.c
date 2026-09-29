#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'removed_elements' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int find_last_removed_position(int *arr, int size, int *removed_elements, int removed_count) {
    if (arr == NULL || removed_elements == NULL || size <= 0 || removed_count <= 0) {
        return -1;
    }
    
    int *removed_flags = (int *)calloc(size, sizeof(int));
    if (removed_flags == NULL) {
        return -1;
    }
    
    for (int i = 0; i < removed_count; i++) {
        for (int j = 0; j < size; j++) {
            if (arr[j] == removed_elements[i] && removed_flags[j] == 0) {
                removed_flags[j] = 1;
                break;
            }
        }
    }
    
    int last_removed_position = -1;
    for (int i = size - 1; i >= 0; i--) {
        if (removed_flags[i] == 1) {
            last_removed_position = i;
            break;
        }
    }
    
    free(removed_flags);
    return last_removed_position;
}

int main(void) {
    int arr[] = {10, 20, 30, 40, 50, 60, 70, 80};
    int removed_elements[] = {30, 50, 10, 70};
    
    int size = sizeof(arr) / sizeof(arr[0]);
    int removed_count = sizeof(removed_elements) / sizeof(removed_elements[0]);
    
    int position = find_last_removed_position(arr, size, removed_elements, removed_count);
    
    if (position != -1) {
        printf("Last removed element position: %d (value: %d)\n", position, arr[position]);
    } else {
        printf("No removed elements found or invalid input.\n");
    }
    
    return 0;
}