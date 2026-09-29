#include <stdio.h>
#include <stdlib.h>

int compare_ints(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;

    if (x < y)
    {
        return -1;
    }
    if (x > y)
    {
        return 1;
    }
    return 0;
}

int min_subsets_distinct(int *arr, size_t n)
{
    size_t i;
    int max_count;
    int count;

    if (arr == NULL || n == 0)
    {
        return 0;
    }

    qsort(arr, n, sizeof(int), compare_ints);

    max_count = 1;
    count = 1;

    for (i = 1; i < n; i++)
    {
        if (arr[i] == arr[i - 1])
        {
            count++;
            if (count > max_count)
            {
                max_count = count;
            }
        }
        else
        {
            count = 1;
        }
    }

    return max_count;
}

int main(void)
{
    int data[] = { 1, 2, 3, 4, 4, 4, 5, 5 };
    size_t n = sizeof(data) / sizeof(data[0]);
    int result;

    result = min_subsets_distinct(data, n);

    if (result <= 0)
    {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (printf("Minimum number of subsets with distinct elements: %d\n", result) < 0)
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}