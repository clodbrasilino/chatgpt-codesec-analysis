#include <stdio.h>

int find_first_duplicate(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] == arr[j]) {
                return arr[i];
            }
        }
    }
    return -1;
}

int main(void) {
    int arr[] = {5, 3, 8, 3, 9, 1, 8, 2};
    int size = sizeof(arr) / sizeof(arr[0]);
    int result = find_first_duplicate(arr, size);
    
    if (result != -1) {
        printf("First duplicate element: %d\n", result);
    } else {
        printf("No duplicate element found\n");
    }
    
    return 0;
}