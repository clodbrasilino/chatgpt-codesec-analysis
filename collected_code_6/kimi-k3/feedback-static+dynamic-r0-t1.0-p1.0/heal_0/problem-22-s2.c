#include <stdio.h>
#include <stdlib.h>

int find_first_duplicate(const int *arr, size_t size, int *duplicate) {
    if (arr == NULL || duplicate == NULL || size == 0) {
        return 0;
    }
    
    for (size_t i = 0; i < size; i++) {
        for (size_t j = i + 1; j < size; j++) {
            if (arr[i] == arr[j]) {
                *duplicate = arr[i];
                return 1;
            }
        }
    }
    
    return 0;
}

int main(void) {
    int arr[] = {4, 2, 7, 8, 2, 9, 4, 1};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int duplicate;
    
    if (find_first_duplicate(arr, size, &duplicate)) {
        printf("First duplicate: %d\n", duplicate);
    } else {
        printf("No duplicates found\n");
    }
    
    return 0;
}