#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stddef.h>

static int max_of_three(int a, int b, int c)
{
    int m = a;
    if (b > m)
    {
        m = b;
    }
    if (c > m)
    {
        m = c;
    }
    return m;
}

static int min_of_three(int a, int b, int c)
{
    int m = a;
    if (b < m)
    {
        m = b;
    }
    if (c < m)
    {
        m = c;
    }
    return m;
}

int find_three_closest(const int *arr1, size_t size1,
                       const int *arr2, size_t size2,
                       const int *arr3, size_t size3,
                       int *result1, int *result2, int *result3,
                       long long *min_diff)
{
    size_t i = 0U;
    size_t j = 0U;
    size_t k = 0U;
    long long best = LLONG_MAX;

    if (arr1 == NULL || arr2 == NULL || arr3 == NULL ||
        result1 == NULL || result2 == NULL || result3 == NULL ||
        min_diff == NULL ||
        size1 == 0U || size2 == 0U || size3 == 0U)
    {
        return -1;
    }

    while (i < size1 && j < size2 && k < size3)
    {
        int a = arr1[i];
        int b = arr2[j];
        int c = arr3[k];
        int hi = max_of_three(a, b, c);
        int lo = min_of_three(a, b, c);
        long long diff = (long long)hi - (long long)lo;

        if (diff < best)
        {
            best = diff;
            *result1 = a;
            *result2 = b;
            *result3 = c;
        }

        if (diff == 0LL)
        {
            break;
        }

        if (a == lo)
        {
            i++;
        }
        else if (b == lo)
        {
            j++;
        }
        else
        {
            k++;
        }
    }

    *min_diff = best;
    return 0;
}

int main(void)
{
    int arr1[] = {1, 4, 10};
    int arr2[] = {2, 15, 20};
    int arr3[] = {10, 12};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    size_t size3 = sizeof(arr3) / sizeof(arr3[0]);
    int r1 = 0;
    int r2 = 0;
    int r3 = 0;
    long long min_diff = 0LL;

    if (find_three_closest(arr1, size1, arr2, size2, arr3, size3,
                           &r1, &r2, &r3, &min_diff) != 0)
    {
        fprintf(stderr, "Error: invalid input provided\n");
        return EXIT_FAILURE;
    }

    printf("Closest elements: %d %d %d\n", r1, r2, r3);
    printf("Minimum difference: %lld\n", min_diff);

    return EXIT_SUCCESS;
}