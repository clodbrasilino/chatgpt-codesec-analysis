#include <stdio.h>
#include <string.h>
#include <stddef.h>

int min_swaps_to_convert(const char *source, const char *target)
{
    size_t len_source;
    size_t len_target;
    size_t i;
    int count_one_zero = 0;
    int count_zero_one = 0;

    if (source == NULL || target == NULL)
    {
        return -1;
    }

    len_source = strlen(source);
    len_target = strlen(target);

    if (len_source != len_target)
    {
        return -1;
    }

    for (i = 0U; i < len_source; ++i)
    {
        char s = source[i];
        char t = target[i];

        if (((s != '0') && (s != '1')) || ((t != '0') && (t != '1')))
        {
            return -1;
        }

        if ((s == '1') && (t == '0'))
        {
            ++count_one_zero;
        }
        else if ((s == '0') && (t == '1'))
        {
            ++count_zero_one;
        }
        else
        {
        }
    }

    if (count_one_zero != count_zero_one)
    {
        return -1;
    }

    return count_one_zero;
}

int main(void)
{
    int result;

    result = min_swaps_to_convert("1101", "0111");
    (void)printf("min_swaps_to_convert(\"1101\", \"0111\") = %d\n", result);

    result = min_swaps_to_convert("111000", "000111");
    (void)printf("min_swaps_to_convert(\"111000\", \"000111\") = %d\n", result);

    result = min_swaps_to_convert("110", "001");
    (void)printf("min_swaps_to_convert(\"110\", \"001\") = %d\n", result);

    result = min_swaps_to_convert("1010", "1010");
    (void)printf("min_swaps_to_convert(\"1010\", \"1010\") = %d\n", result);

    result = min_swaps_to_convert("101", "1010");
    (void)printf("min_swaps_to_convert(\"101\", \"1010\") = %d\n", result);

    result = min_swaps_to_convert(NULL, "1010");
    (void)printf("min_swaps_to_convert(NULL, \"1010\") = %d\n", result);

    result = min_swaps_to_convert("10a1", "1010");
    (void)printf("min_swaps_to_convert(\"10a1\", \"1010\") = %d\n", result);

    return 0;
}