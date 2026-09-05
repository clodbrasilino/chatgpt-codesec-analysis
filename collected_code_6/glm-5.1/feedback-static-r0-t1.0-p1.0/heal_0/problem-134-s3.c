#include <stdio.h>
#include <stdlib.h>

int check_last_element(int *array, size_t size, size_t p) {
    if (size == 0) {
        return -1;
    }

    for (size_t i = 0; i < p; i++) {
        array[size - 1] = array[size - 1] + 1;
    }

    if (array[size - 1] % 2 == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main(void) {
    int arr[] = {1, 2, 3, 4, 5};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    size_t p = 3;
    
    int result = check_last_element(arr, size, p);
    
    if (result == 1) {
        printf("Even\n");
    } else if (result == 0) {
        printf("Odd\n");
    } else {
        printf("Error: Empty array\n");
    }
    
    return 0;
}