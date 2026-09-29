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
     * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000002,time:16809,execs:6719,op:havoc,rep:5)
     */
    int64_t first = (l % 2 == 0) ? l : l + 1;
    int64_t last = (r % 2 == 0) ? r : r - 1;

    if (first > last)
    {
        return 0;
    }

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775806 - -9223372036854775808 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000002,time:16809,execs:6719,op:havoc,rep:5)
     */
    int64_t count = (last - first) / 2 + 1;
    
    if (count == 0)
    {
        return 0;
    }
    
    if (first > 0 && last > 0)
    {
        if (first > INT64_MAX - last)
        {
            return 0;
        }
        int64_t sum_fl = first + last;
        if (count > INT64_MAX / sum_fl)
        {
            return 0;
        }
    }
    else if (first < 0 && last < 0)
    {
        if (first < INT64_MIN - last)
        {
            return 0;
        }
        int64_t sum_fl = first + last;
        if (sum_fl != 0 && count < INT64_MIN / sum_fl)
        {
            return 0;
        }
    }
    else
    {
        int64_t sum_fl = first + last;
        if (sum_fl > 0)
        {
            if (count > INT64_MAX / sum_fl)
            {
                return 0;
            }
        }
        /* Possible weaknesses found:
         *  Assuming that condition 'sum_fl<0' is not redundant
         */
        else if (sum_fl < 0)
        {
            /* Possible weaknesses found:
             *  Expression 'sum_fl' can have a negative value. That is converted to an unsigned value and used in an unsigned calculation. [signConversionCond]
             *  Negative value is converted to an unsigned value
             */
            if (count < INT64_MIN / sum_fl)
            {
                return 0;
            }
        }
    }
    
    int64_t sum_fl = first + last;
    int64_t product = count * sum_fl;
    
    if (product % 2 != 0)
    {
        return 0;
    }
    
    return product / 2;
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