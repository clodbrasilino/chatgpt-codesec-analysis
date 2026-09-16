#include <stdio.h>
#include <stdlib.h>

int* remove_element(int *array, size_t *size, int index) {
    if (index < 0 || index >= *size) {
        return NULL;
    }
    int *new_array = (int*) malloc((*size - 1) * sizeof(int));
    for (size_t i = 0; i < *size; i++) {
        if (i < index) {
            new_array[i] = array[i];
        } else if (i > index) {
            new_array[i-1] = array[i];
        }
    }
    free(array);
    *size -= 1;
    return new_array;
}

int find_last_removed_position(int *array, size_t size, int value) {
    for (size_t i = 0; i < size; i++) {
        int *new_array = remove_element(array, &size, i);
        if (new_array == NULL) {
            return -1;
        }
        int last_removed_value = array[i];
        free(new_array);
        if (last_removed_value == value) {
            return i;
        }
        array = new_array;
    }
    return -1;
}

int main() {
    int array[] = {1, 2, 3, 4, 5};
    size_t size = sizeof(array) / sizeof(array[0]);
    int position = find_last_removed_position(array, size, 3);
    printf("Position of the last removed element: %d\n", position);
    return 0;
}