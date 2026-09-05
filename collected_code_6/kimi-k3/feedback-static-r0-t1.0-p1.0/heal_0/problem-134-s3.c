#include <stdio.h>
#include <stdlib.h>

void check_last_element_parity(int *arr, size_t size, unsigned int p) {
    if (arr == NULL || size == 0) {
        fprintf(stderr, "Invalid input parameters\n");
        return;
    }
    
    for (unsigned int i = 0; i < p; i++) {
        arr[size - 1] *= 2;
    }
    
    if (arr[size - 1] % 2 == 0) {
        printf("Last element is even\n");
    } else {
        printf("Last element is odd\n");
    }
}

int main(void) {
    size_t size = 5;
    int *arr = malloc(size * sizeof(int));
    
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    arr[3] = 4;
    arr[4] = 5;
    
    unsigned int p = 3;
    
    check_last_element_parity(arr, size, p);
    
    free(arr);
    arr = NULL;
    
    return EXIT_SUCCESS;
}