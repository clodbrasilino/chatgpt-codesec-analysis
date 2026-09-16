#include <stdio.h>
#include <stdlib.h>

int longest_bitonic_subsequence(const int arr[], int n)
{
    int *inc;
    int *dec;
    int i;
    int j;
    int max_len;

    if (arr == NULL || n <= 0)
    {
        return 0;
    }

    inc = (int *)malloc((size_t)n * sizeof(int));
    if (inc == NULL)
    {
        return -1;
    }

    dec = (int *)malloc((size_t)n * sizeof(int));
    if (dec == NULL)
    {
        free(inc);
        return -1;
    }

    for (i = 0; i < n; i++)
    {
        inc[i] = 1;
        dec[i] = 1;
    }

    for (i = 1; i < n; i++)
    {
        for (j = 0; j < i; j++)
        {
            if (arr[i] > arr[j] && inc[i] < inc[j] + 1)
            {
                inc[i] = inc[j] + 1;
            }
        }
    }

    for (i = n - 2; i >= 0; i--)
    {
        for (j = n - 1; j > i; j--)
        {
            if (arr[i] > arr[j] && dec[i] < dec[j] + 1)
            {
                dec[i] = dec[j] + 1;
            }
        }
    }

    max_len = inc[0] + dec[0] - 1;

    for (i = 1; i < n; i++)
    {
        if (inc[i] + dec[i] - 1 > max_len)
        {
            max_len = inc[i] + dec[i] - 1;
        }
    }

    free(inc);
    free(dec);

    return max_len;
}

int main(void)
{
    int arr[] = {1, 11, 2, 10, 4, 5, 2, 1};
    int n = (int)(sizeof(arr) / sizeof(arr[0]));
    int result;

    result = longest_bitonic_subsequence(arr, n);

    if (result < 0)
    {
        fprintf(stderr, "Error: memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Length of longest bitonic subsequence: %d\n", result);

    return EXIT_SUCCESS;
}