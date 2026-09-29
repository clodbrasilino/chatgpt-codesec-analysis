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

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000001,time:11367,execs:3564,op:havoc,rep:4)
     */
    int64_t first = (l % 2 == 0) ? l : l + 1;
    int64_t last = (r % 2 == 0) ? r : r - 1;

    if (first > last)
    {
        return 0;
    }

    uint64_t uf = (uint64_t)first;
    uint64_t ul = (uint64_t)last;
    uint64_t count = (ul - uf) / 2 + 1;
    uint64_t sum = uf + ul;
    uint64_t result;

    if (count % 2 == 0)
    {
        result = (count / 2) * sum;
    }
    else
    {
        result = count * (sum / 2);
    }

    return (int64_t)result;
}

int main(void)
{
    int64_t l, r;

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNd64, &l) != 1)
    {
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNd64, &r) != 1)
    {
        return 1;
    }

    printf("%" PRId64 "\n", sum_even_natural(l, r));
    return 0;
}