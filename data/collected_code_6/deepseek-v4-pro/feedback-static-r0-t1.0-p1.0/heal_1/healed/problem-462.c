#include <stdio.h>
#include <stdlib.h>

int** subsets(const int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    int totalSubsets = 1 << numsSize;
    int** result = (int**)malloc(totalSubsets * sizeof(int*));
    if (!result) {
        *returnSize = 0;
        return NULL;
    }
    
    *returnColumnSizes = (int*)malloc(totalSubsets * sizeof(int));
    if (!*returnColumnSizes) {
        free(result);
        *returnSize = 0;
        return NULL;
    }
    
    for (int i = 0; i < totalSubsets; i++) {
        int count = 0;
        for (int j = 0; j < numsSize; j++) {
            if (i & (1 << j)) {
                count++;
            }
        }
        
        (*returnColumnSizes)[i] = count;
        result[i] = (int*)malloc(count * sizeof(int));
        if (!result[i]) {
            for (int k = 0; k < i; k++) {
                free(result[k]);
            }
            free(result);
            free(*returnColumnSizes);
            *returnSize = 0;
            return NULL;
        }
        
        int index = 0;
        for (int j = 0; j < numsSize; j++) {
            if (i & (1 << j)) {
                result[i][index++] = nums[j];
            }
        }
    }
    
    *returnSize = totalSubsets;
    return result;
}

int main(void) {
    int nums[] = {1, 2, 3};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int returnSize;
    int* returnColumnSizes;
    
    int** result = subsets(nums, numsSize, &returnSize, &returnColumnSizes);
    if (!result) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    for (int i = 0; i < returnSize; i++) {
        printf("[");
        for (int j = 0; j < returnColumnSizes[i]; j++) {
            printf("%d", result[i][j]);
            if (j < returnColumnSizes[i] - 1) {
                printf(", ");
            }
        }
        printf("]\n");
        free(result[i]);
    }
    
    free(result);
    free(returnColumnSizes);
    
    return 0;
}