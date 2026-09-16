#include <stdio.h>

void rearrange_negatives_first(int arr[], int size) {
    int left = 0;
    int right = size - 1;
    
    while (left < right) {
        while (left < size && arr[left] < 0) {
            left++;
        }
        
        while (right >= 0 && arr[right] >= 0) {
            right--;
        }
        
        if (left < right) {
            int temp = arr[left];
            arr[left] = arr[right];
            arr[right] = temp;
            left++;
            right--;
        }
    }
}

int main(void) {
    int test_array[] = {-1, 5, -3, 2, -8, 7, -4, 6};
    int size = sizeof(test_array) / sizeof(test_array[0]);
    int i;
    
    printf("Original array: ");
    for (i = 0; i < size; i++) {
        printf("%d ", test_array[i]);
    }
    printf("\n");
    
    rearrange_negatives_first(test_array, size);
    
    printf("Rearranged array: ");
    for (i = 0; i < size; i++) {
        printf("%d ", test_array[i]);
    }
    printf("\n");
    
    return 0;
}