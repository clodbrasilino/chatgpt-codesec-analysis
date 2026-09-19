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

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000002,time:9388,execs:3736,op:havoc,rep:8)
     */
    int64_t first = (l % 2 == 0) ? l : l + 1;
    int64_t last = (r % 2 == 0) ? r : r - 1;

    if (first > last)
    {
        return 0;
    }

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775806 - -9223372036854775808 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000002,time:9388,execs:3736,op:havoc,rep:8)
     */
    int64_t count = (last - first) / 2 + 1;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 8888888 + 9223372036854775806 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000002,sig:06,src:000005,time:12599,execs:5077,op:havoc,rep:3)
     * UBSan: signed integer overflow: 4611686018422943460 * -9223372036845886922 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000002,sig:06,src:000005,time:12599,execs:5077,op:havoc,rep:3)
     * UBSan: signed integer overflow: 3333333333333333330 * 6666666666666666666 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000004,time:2708,execs:1116,op:havoc,rep:2)
     */
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