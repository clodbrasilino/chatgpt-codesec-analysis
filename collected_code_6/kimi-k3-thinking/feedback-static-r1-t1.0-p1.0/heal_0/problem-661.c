#include <stdio.h>
#include <stddef.h>

static long long ll_max(long long a, long long b)
{
    return (a > b) ? a : b;
}

long long max_sum_no_three_consecutive(const int *arr, size_t n)
{
    long long dp0;
    long long dp1;
    long long dp2;
    long long curr;
    size_t i;

    if (arr == NULL || n == 0U)
    {
        return 0LL;
    }

    dp0 = 0LL;
    dp1 = ll_max(0LL, (long long)arr[0]);

    if (n == 1U)
    {
        return dp1;
    }

    dp2 = ll_max(dp1, dp1 + (long long)arr[1]);

    for (i = 3U; i <= n; ++i)
    {
        curr = ll_max(dp2,
                      ll_max(dp1 + (long long)arr[i - 1U],
                             dp0 + (long long)arr[i - 2U] + (long long)arr[i - 1U]));
        dp0 = dp1;
        dp1 = dp2;
        dp2 = curr;
    }

    return dp2;
}

int main(void)
{
    const int test1[] = {1, 2, 3};
    const int test2[] = {100, 1000, 100, 1000, 1};
    const int test3[] = {3000, 2000, 1000, 3, 10};
    const int test4[] = {-5, -1, -2, -3};
    const int test5[] = {1, 2, 9, 4, 5, 0, 4, 11, 6};

    printf("%lld\n", max_sum_no_three_consecutive(test1, sizeof(test1) / sizeof(test1[0])));
    printf("%lld\n", max_sum_no_three_consecutive(test2, sizeof(test2) / sizeof(test2[0])));
    printf("%lld\n", max_sum_no_three_consecutive(test3, sizeof(test3) / sizeof(test3[0])));
    printf("%lld\n", max_sum_no_three_consecutive(test4, sizeof(test4) / sizeof(test4[0])));
    printf("%lld\n", max_sum_no_three_consecutive(test5, sizeof(test5) / sizeof(test5[0])));

    return 0;
}