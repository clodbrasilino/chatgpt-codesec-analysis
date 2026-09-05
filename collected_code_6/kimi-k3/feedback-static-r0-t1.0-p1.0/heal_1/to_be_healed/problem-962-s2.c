#include <stdio.h>
#include <stdint.h>

int64_t sum_even_natural(int64_t l, int64_t r)
{
    if (l > r || r < 2)
    {
        return 0;
    }

    if (l < 2)
    {
        l = 2;
    }

    int64_t first = (l % 2 == 0) ? l : l + 1;
    int64_t last = (r % 2 == 0) ? r : r - 1;

    if (first > last)
    {
        return 0;
    }

    int64_t count = (last - first) / 2 + 1;
    return count * (first + last) / 2;
}

int main(void)
{
    int64_t l, r;

    /* Possible weaknesses found:
     *  %lld in format string (no. 2) requires 'long long *' but the argument type is 'signed long *'. [invalidScanfArgType_int]
     *  %lld in format string (no. 1) requires 'long long *' but the argument type is 'signed long *'. [invalidScanfArgType_int]
     */
    if (scanf("%lld %lld", &l, &r) != 2)
    {
        return 1;
    }

    /* Possible weaknesses found:
     *  %lld in format string (no. 1) requires 'long long' but the argument type is 'signed long'. [invalidPrintfArgType_sint]
     */
    printf("%lld\n", sum_even_natural(l, r));
    return 0;
}