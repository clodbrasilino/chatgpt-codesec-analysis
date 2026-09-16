#include <stdio.h>
#include <stdlib.h>

void moveZeroes(int* nums, int numsSize) {
    if (nums == NULL || numsSize <= 0) {
        return;
    }

    int insertPos = 0;

    for (int i = 0; i < numsSize; i++) {
        if (nums[i] != 0) {
            nums[insertPos++] = nums[i];
        }
    }

    while (insertPos < numsSize) {
        nums[insertPos++] = 0;
    }
}

int main() {
    int arr[] = {0, 1, 0, 3, 12};
    int size = sizeof(arr) / sizeof(arr[0]);

    moveZeroes(arr, size);

    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}