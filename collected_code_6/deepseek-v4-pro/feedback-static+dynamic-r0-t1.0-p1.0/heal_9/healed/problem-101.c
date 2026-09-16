#include <stdio.h>
#include <stdlib.h>

int find_kth_element(const int *arr, int size, int k, int *value) {
    if (arr == NULL || size <= 0 || k < 0 || k >= size || value == NULL) {
        fprintf(stderr, "Invalid input parameters\n");
        return -1;
    }
    *value = arr[k];
    return 0;
}

int main(void) {
    int arr[] = {10, 20, 30, 40, 50};
    int size = sizeof(arr) / sizeof(arr[0]);
    
    for (int k = 0; k < size; k++) {
        int result;
        if (find_kth_element(arr, size, k, &result) == 0) {
            printf("The %dth element is: %d\n", k, result);
        }
    }
    
    return 0;
}