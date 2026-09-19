#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

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
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 11111111000000001 * 22222222444444444 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000001,time:2796,execs:1287,op:havoc,rep:4)
     * UBSan: signed integer overflow: 4611686018427387902 * -9223372036854775806 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000002,time:915,execs:439,op:havoc,rep:6)
     * UBSan: signed integer overflow: 4 + 9223372036854775806 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000002,time:915,execs:439,op:havoc,rep:6)
     */
    return count * (first + last) / 2;
}

int main(void)
{
    int64_t l, r;

    if (scanf("%" SCNd64 " %" SCNd64, &l, &r) != 2)
    {
        return 1;
    }

    printf("%" PRId64 "\n", sum_even_natural(l, r));
    return 0;
}