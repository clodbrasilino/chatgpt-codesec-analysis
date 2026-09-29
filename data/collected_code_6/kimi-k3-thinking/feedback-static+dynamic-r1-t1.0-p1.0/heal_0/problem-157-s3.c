#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

int *decompressRLElist(const int *nums, int numsSize, int *returnSize)
{
    size_t total;
    size_t index;
    int *result;
    int i;
    int j;

    if (nums == NULL || returnSize == NULL || numsSize <= 0 || (numsSize % 2) != 0)
    {
        if (returnSize != NULL)
        {
            *returnSize = 0;
        }
        return NULL;
    }

    total = 0;
    for (i = 0; i < numsSize; i += 2)
    {
        if (nums[i] < 0)
        {
            *returnSize = 0;
            return NULL;
        }
        total += (size_t)nums[i];
    }

    if (total > (size_t)INT_MAX || total > SIZE_MAX / sizeof(int))
    {
        *returnSize = 0;
        return NULL;
    }

    result = NULL;
    if (total > 0)
    {
        result = malloc(total * sizeof(*result));
        if (result == NULL)
        {
            *returnSize = 0;
            return NULL;
        }
    }

    index = 0;
    for (i = 0; i < numsSize; i += 2)
    {
        for (j = 0; j < nums[i]; j++)
        {
            result[index] = nums[i + 1];
            index++;
        }
    }

    *returnSize = (int)total;
    return result;
}

int main(void)
{
    int nums[] = {1, 2, 3, 4};
    int returnSize;
    int *decompressed;
    int i;

    returnSize = 0;
    decompressed = decompressRLElist(nums, (int)(sizeof(nums) / sizeof(nums[0])), &returnSize);
    if (decompressed == NULL && returnSize != 0)
    {
        return EXIT_FAILURE;
    }

    for (i = 0; i < returnSize; i++)
    {
        printf("%d ", decompressed[i]);
    }
    printf("\n");

    free(decompressed);
    decompressed = NULL;

    return EXIT_SUCCESS;
}