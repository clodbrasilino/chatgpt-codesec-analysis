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
        else if (sum_fl < 0)
        {
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