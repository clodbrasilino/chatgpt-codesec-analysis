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

/* Possible weaknesses found:
 *  Parameter 'nums' can be declared as pointer to const [constParameterPointer]
 */
void printArray(int* nums, int numsSize) {
    if (nums == NULL || numsSize <= 0) {
        return;
    }
    
    for (int i = 0; i < numsSize; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
}

int main() {
    int nums[] = {0, 1, 0, 3, 12};
    int numsSize = sizeof(nums) / sizeof(nums[0]);

    moveZeroes(nums, numsSize);
    printArray(nums, numsSize);

    return 0;
}