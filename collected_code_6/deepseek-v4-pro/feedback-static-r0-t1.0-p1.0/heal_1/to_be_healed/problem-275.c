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

    int last_removed = removed_elements[removed_count - 1];
    
    for (int i = 0; i < size; i++) {
        if (arr[i] == last_removed) {
            return i;
        }
    }
    
    return -1;
}

int main(void) {
    int arr[] = {10, 20, 30, 40, 50};
    int size = sizeof(arr) / sizeof(arr[0]);
    int removed_elements[] = {20, 40, 30};
    int removed_count = sizeof(removed_elements) / sizeof(removed_elements[0]);
    
    int position = find_last_removed_position(arr, size, removed_elements, removed_count);
    
    printf("Last removed element position: %d\n", position);
    
    return 0;
}