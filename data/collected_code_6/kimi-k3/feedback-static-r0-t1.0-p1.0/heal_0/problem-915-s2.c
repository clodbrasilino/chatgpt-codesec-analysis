#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void rearrange_positive_negative(int arr[], int size) {
    if (arr == NULL || size <= 0) {
        return;
    }
    
    int *temp = (int *)malloc(size * sizeof(int));
    if (temp == NULL) {
        return;
    }
    
    int pos_index = 0;
    int neg_index = size - 1;
    
    for (int i = 0; i < size; i++) {
        if (arr[i] >= 0) {
            temp[pos_index++] = arr[i];
        } else {
            temp[neg_index--] = arr[i];
        }
    }
    
    for (int i = 0; i < size; i++) {
        arr[i] = temp[i];
    }
    
    free(temp);
    temp = NULL;
}

void print_array(const int arr[], int size) {
    if (arr == NULL || size <= 0) {
        return;
    }
    
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void) {
    int arr[] = {-1, 2, -3, 4, 5, -6, -7, 8, 9};
    int size = sizeof(arr) / sizeof(arr[0]);
    
    printf("Original array: ");
    print_array(arr, size);
    
    rearrange_positive_negative(arr, size);
    
    printf("Rearranged array: ");
    print_array(arr, size);
    
    return 0;
}