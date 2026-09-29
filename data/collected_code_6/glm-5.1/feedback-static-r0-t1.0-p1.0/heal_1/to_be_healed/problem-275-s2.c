#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'removed_elements' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'array' can be declared as pointer to const [constParameterPointer]
 */
int find_last_removed_position(int *array, size_t original_size, int *removed_elements, size_t removed_count) {
    if (array == NULL || removed_elements == NULL) {
        return -1;
    }
    if (original_size == 0 && removed_count == 0) {
        return -1;
    }

    for (size_t i = removed_count; i > 0; i--) {
        int target = removed_elements[i - 1];
        for (size_t j = 0; j < original_size; j++) {
            if (array[j] == target) {
                return (int)j;
            }
        }
    }
    
    return -1;
}

int main(void) {
    int array[] = {10, 20, 30, 40, 50};
    size_t original_size = sizeof(array) / sizeof(array[0]);
    int removed_elements[] = {20, 40};
    size_t removed_count = sizeof(removed_elements) / sizeof(removed_elements[0]);

    int position = find_last_removed_position(array, original_size, removed_elements, removed_count);

    printf("%d\n", position);

    return 0;
}