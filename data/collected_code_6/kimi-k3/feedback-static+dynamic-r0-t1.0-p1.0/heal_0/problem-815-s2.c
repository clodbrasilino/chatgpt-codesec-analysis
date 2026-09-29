#include <stdio.h>
#include <stdlib.h>

void sort_array(int arr[], int size) {
    if (arr == NULL || size <= 0) {
        return;
    }
    
    int count_0 = 0;
    int count_1 = 0;
    int count_2 = 0;
    
    for (int i = 0; i < size; i++) {
        if (arr[i] == 0) {
            count_0++;
        } else if (arr[i] == 1) {
            count_1++;
        } else if (arr[i] == 2) {
            count_2++;
        }
    }
    
    int index = 0;
    
    for (int i = 0; i < count_0; i++) {
        arr[index++] = 0;
    }
    
    for (int i = 0; i < count_1; i++) {
        arr[index++] = 1;
    }
    
    for (int i = 0; i < count_2; i++) {
        arr[index++] = 2;
    }
}

int main(void) {
    int arr[] = {2, 0, 1, 2, 1, 0, 0, 2, 1};
    int size = sizeof(arr) / sizeof(arr[0]);
    
    printf("Original array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    sort_array(arr, size);
    
    printf("Sorted array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    return 0;
}