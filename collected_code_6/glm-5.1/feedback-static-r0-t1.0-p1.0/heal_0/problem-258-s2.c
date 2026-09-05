#include <stdio.h>
#include <stdlib.h>

size_t count_odd(int *list, size_t size) {
    if (list == NULL) {
        return 0;
    }

    size_t count = 0;
    for (size_t i = 0; i < size; i++) {
        if (list[i] % 2 != 0) {
            count++;
        }
    }
    return count;
}

int main(void) {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    
    size_t odd_count = count_odd(arr, size);
    
    printf("%zu\n", odd_count);
    
    return 0;
}