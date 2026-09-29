#include <stdio.h>
#include <stdlib.h>

int find_kth_element(const int *array, size_t size, size_t k, int *result) {
    if (array == NULL || result == NULL) {
        return -1;
    }
    if (k >= size) {
        return -1;
    }
    
    *result = array[k];
    return 0;
}

int main(void) {
    int array[] = {10, 20, 30, 40, 50};
    size_t size = sizeof(array) / sizeof(array[0]);
    size_t k = 2;
    int result = 0;

    int status = find_kth_element(array, size, k, &result);

    if (status == 0) {
        printf("Element at index %zu is %d\n", k, result);
    } else {
        printf("Failed to find the element. Invalid array, null pointer, or index out of bounds.\n");
    }

    return 0;
}