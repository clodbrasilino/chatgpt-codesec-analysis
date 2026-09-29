#include <stdio.h>

void moveZeroes(int* nums, int numsSize) {
    if(numsSize > 1) {
        int insertPos = 0;
        for (int i = 0; i < numsSize; i++) {
            if (nums[i] != 0) {
                nums[insertPos++] = nums[i];
            }
        }
        
        while(insertPos < numsSize){
            nums[insertPos++] = 0;
        }
    }
}

#define SIZE 6

int main() {
    int arr[SIZE] = {0, 1, 0, 3, 12, 0};
    moveZeroes(arr, SIZE);
    for(int i=0; i < SIZE; i++) {
        printf("%d ", arr[i]);
    }
    return 0;
}