#include <stdio.h>
#include <stddef.h>

static int max2(int a, int b)
{
    return (a > b) ? a : b;
}

static int max3(int a, int b, int c)
{
    return max2(max2(a, b), c);
}

int maxSumNoThreeConsecutive(const int arr[], size_t n)
{
    size_t i;
    int sum_im3;
    int sum_im2;
    int sum_im1;

    if (arr == NULL || n == 0U)
    {
        return 0;
    }

    if (n == 1U)
    {
        return arr[0];
    }

    if (n == 2U)
    {
        return arr[0] + arr[1];
    }

    sum_im3 = arr[0];
    sum_im2 = arr[0] + arr[1];
    sum_im1 = max3(sum_im2, arr[0] + arr[2], arr[1] + arr[2]);

    for (i = 3U; i < n; ++i)
    {
        int current = max3(sum_im1, sum_im2 + arr[i], sum_im3 + arr[i - 1U] + arr[i]);
        sum_im3 = sum_im2;
        sum_im2 = sum_im1;
        sum_im1 = current;
    }

    return sum_im1;
}

int main(void)
{
    const int arr1[] = {100, 1000, 100, 1000, 1};
    const int arr2[] = {3000, 2000, 1000, 3, 10};
    const int arr3[] = {1, 2, 3, 4, 5, 6, 7, 8};

    printf("%d\n", maxSumNoThreeConsecutive(arr1, sizeof(arr1) / sizeof(arr1[0])));
    printf("%d\n", maxSumNoThreeConsecutive(arr2, sizeof(arr2) / sizeof(arr2[0])));
    printf("%d\n", maxSumNoThreeConsecutive(arr3, sizeof(arr3) / sizeof(arr3[0])));

    return 0;
}