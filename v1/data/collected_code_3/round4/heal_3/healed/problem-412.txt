#include <stdio.h>
#include <stdlib.h>

int* removeOdd(int* nums, int numsSize, int* returnSize) {
    int* result = (int*)malloc(numsSize * sizeof(int));

    if (result == NULL) {
        *returnSize = 0;
        return NULL;
    }

    int j = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] % 2 == 0) {
            result[j++] = nums[i];
        }
    }

    *returnSize = j;
    int* tmp = realloc(result, j * sizeof(int));

    if (tmp == NULL) {
        free(result);
        *returnSize = 0;
        return NULL;
    } else {
        result = tmp;
    }

    return result;
}

int main() {
    int nums[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int returnSize = 0;
    int* result = removeOdd(nums, numsSize, &returnSize);

    if(result != NULL) {
        for (int i = 0; i < returnSize; i++) {
            printf("%d ", result[i]);
        }
        free(result);
    }

    return 0;
}
