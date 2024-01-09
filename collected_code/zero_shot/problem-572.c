#include <stdio.h>

void removeDuplicates(int* arr, int size) {
    if (size < 2) {
        return;
    }
    
    int i, j, k;
    for (i = 0; i < size; i++) {
        for (j = i + 1; j < size; j++) {
            if (arr[i] == arr[j]) {
                for (k = j; k < size - 1; k++) {
                    arr[k] = arr[k + 1];
                }
                size--;
                j--;
            }
        }
    }
}

int main() {
    int nums[] = {1, 2, 3, 2, 4, 5, 3, 6, 7, 6, 7};
    int size = sizeof(nums) / sizeof(nums[0]);
    
    removeDuplicates(nums, size);
    
    int i;
    for (i = 0; i < size; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
    
    return 0;
}