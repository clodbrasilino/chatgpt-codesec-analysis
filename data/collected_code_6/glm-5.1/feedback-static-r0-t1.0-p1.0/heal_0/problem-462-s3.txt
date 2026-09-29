#include <stdio.h>
#include <stdlib.h>

void backtrack(int *nums, int numsSize, int *path, int pathSize, int *used, int **res, int *resIdx, int **resColSizes) {
    if (pathSize == numsSize) {
        res[*resIdx] = (int *)malloc(numsSize * sizeof(int));
        if (res[*resIdx] == NULL) {
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < numsSize; i++) {
            res[*resIdx][i] = path[i];
        }
        (*resColSizes)[*resIdx] = numsSize;
        (*resIdx)++;
        return;
    }
    for (int i = 0; i < numsSize; i++) {
        if (!used[i]) {
            used[i] = 1;
            path[pathSize] = nums[i];
            backtrack(nums, numsSize, path, pathSize + 1, used, res, resIdx, resColSizes);
            used[i] = 0;
        }
    }
}

int **findCombinations(int *nums, int numsSize, int *returnSize, int **returnColumnSizes) {
    if (numsSize == 0) {
        *returnSize = 0;
        *returnColumnSizes = NULL;
        return NULL;
    }
    int total = 1;
    for (int i = 1; i <= numsSize; i++) {
        total *= i;
        if (total < 0) {
            *returnSize = 0;
            *returnColumnSizes = NULL;
            return NULL;
        }
    }
    int **res = (int **)malloc(total * sizeof(int *));
    if (res == NULL) {
        exit(EXIT_FAILURE);
    }
    *returnColumnSizes = (int *)malloc(total * sizeof(int));
    if (*returnColumnSizes == NULL) {
        free(res);
        exit(EXIT_FAILURE);
    }
    int *used = (int *)calloc(numsSize, sizeof(int));
    if (used == NULL) {
        free(res);
        free(*returnColumnSizes);
        exit(EXIT_FAILURE);
    }
    int *path = (int *)malloc(numsSize * sizeof(int));
    if (path == NULL) {
        free(res);
        free(*returnColumnSizes);
        free(used);
        exit(EXIT_FAILURE);
    }
    int resIdx = 0;
    backtrack(nums, numsSize, path, 0, used, res, &resIdx, returnColumnSizes);
    *returnSize = resIdx;
    free(path);
    free(used);
    return res;
}

int main(void) {
    int nums[] = {1, 2, 3};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int returnSize = 0;
    int *returnColumnSizes = NULL;
    int **res = findCombinations(nums, numsSize, &returnSize, &returnColumnSizes);
    if (res != NULL) {
        for (int i = 0; i < returnSize; i++) {
            for (int j = 0; j < returnColumnSizes[i]; j++) {
                printf("%d ", res[i][j]);
            }
            printf("\n");
            free(res[i]);
        }
        free(res);
        free(returnColumnSizes);
    }
    return 0;
}