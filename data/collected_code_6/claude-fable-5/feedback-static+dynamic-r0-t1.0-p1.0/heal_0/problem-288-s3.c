#include <stdio.h>
#include <stdlib.h>

static long long mod_value(long long value, long long p)
{
    long long r = value % p;
    if (r < 0)
    {
        r += p;
    }
    return r;
}

size_t count_self_inverse(const long long *arr, size_t n, long long p)
{
    size_t count = 0U;
    size_t i;

    if ((arr == NULL) || (p <= 1))
    {
        return 0U;
    }

    for (i = 0U; i < n; i++)
    {
        long long x = mod_value(arr[i], p);
        if (((x * x) % p) == 1)
        {
            count++;
        }
    }

    return count;
}

int main(void)
{
    long long data[] = { 1, 6, 4, 5, 2, 3 };
    size_t n = sizeof(data) / sizeof(data[0]);
    long long p = 7;
    size_t result;

    result = count_self_inverse(data, n, p);

    if (printf("Count: %zu\n", result) < 0)
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}