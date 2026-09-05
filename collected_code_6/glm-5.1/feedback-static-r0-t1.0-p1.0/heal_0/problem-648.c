#include <stdio.h>
#include <stdlib.h>

int swap_nth(int *list, size_t size, size_t n) {
    if (list == NULL || n == 0) {
        return -1;
    }
    
    for (size_t i = n - 1; i + 1 < size; i += n) {
        int temp = list[i];
        list[i] = list[i + 1];
        list[i + 1] = temp;
    }
    
    return 0;
}

int main(void) {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    size_t n = 2;
    
    if (swap_nth(arr, size, n) != 0) {
        return EXIT_FAILURE;
    }
    
    for (size_t i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    return EXIT_SUCCESS;
}