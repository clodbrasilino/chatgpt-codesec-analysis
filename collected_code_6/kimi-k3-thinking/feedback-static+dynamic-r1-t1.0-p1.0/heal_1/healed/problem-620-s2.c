#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>

static int compare_ints(const void *lhs, const void *rhs)
{
    int a = *(const int *)lhs;
    int b = *(const int *)rhs;

    if (a < b)
    {
        return -1;
    }
    if (a > b)
    {
        return 1;
    }
    return 0;
}

static int is_divisible(int value, int divisor)
{
    if (divisor == 0)
    {
        return 0;
    }
    if (value == INT_MIN && divisor == -1)
    {
        return 1;
    }
    return value % divisor == 0;
}

int *largest_divisible_subset(const int *nums, int nums_size, int *subset_size)
{
    int *sorted;
    int *dp;
    int *parent;
    int *result;
    int max_index;
    int count;
    int idx;
    int i;
    int j;

    if (subset_size == NULL)
    {
        return NULL;
    }
    *subset_size = 0;

    if (nums == NULL || nums_size <= 0)
    {
        return NULL;
    }

    if ((size_t)nums_size > SIZE_MAX / sizeof(*sorted))
    {
        return NULL;
    }

    sorted = malloc((size_t)nums_size * sizeof(*sorted));
    if (sorted == NULL)
    {
        return NULL;
    }

    for (i = 0; i < nums_size; i++)
    {
        sorted[i] = nums[i];
    }

    qsort(sorted, (size_t)nums_size, sizeof(*sorted), compare_ints);

    dp = malloc((size_t)nums_size * sizeof(*dp));
    if (dp == NULL)
    {
        free(sorted);
        return NULL;
    }

    parent = malloc((size_t)nums_size * sizeof(*parent));
    if (parent == NULL)
    {
        free(dp);
        free(sorted);
        return NULL;
    }

    max_index = 0;
    for (i = 0; i < nums_size; i++)
    {
        dp[i] = 1;
        parent[i] = -1;
        for (j = 0; j < i; j++)
        {
            if (is_divisible(sorted[i], sorted[j]) && dp[j] + 1 > dp[i])
            {
                dp[i] = dp[j] + 1;
                parent[i] = j;
            }
        }
        if (dp[i] > dp[max_index])
        {
            max_index = i;
        }
    }

    count = dp[max_index];

    if ((size_t)count > SIZE_MAX / sizeof(*result))
    {
        free(parent);
        free(dp);
        free(sorted);
        return NULL;
    }

    result = malloc((size_t)count * sizeof(*result));
    if (result == NULL)
    {
        free(parent);
        free(dp);
        free(sorted);
        return NULL;
    }

    idx = max_index;
    while (idx != -1 && count > 0)
    {
        count--;
        result[count] = sorted[idx];
        idx = parent[idx];
    }

    *subset_size = dp[max_index];

    free(parent);
    free(dp);
    free(sorted);

    return result;
}

int main(void)
{
    int nums[] = {1, 2, 4, 8, 3, 6, 12, 24};
    int nums_size = (int)(sizeof(nums) / sizeof(nums[0]));
    int subset_size;
    int *subset;
    int i;

    subset = largest_divisible_subset(nums, nums_size, &subset_size);
    if (subset == NULL)
    {
        fprintf(stderr, "Error: unable to compute largest divisible subset.\n");
        return EXIT_FAILURE;
    }

    printf("Largest divisible subset (size %d):", subset_size);
    for (i = 0; i < subset_size; i++)
    {
        printf(" %d", subset[i]);
    }
    printf("\n");

    free(subset);

    return EXIT_SUCCESS;
}