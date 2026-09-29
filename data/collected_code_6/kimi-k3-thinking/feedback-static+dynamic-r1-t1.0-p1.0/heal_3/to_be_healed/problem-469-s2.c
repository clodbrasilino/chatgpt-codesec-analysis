#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>

static long long llmax(long long a, long long b)
{
    return (a > b) ? a : b;
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 7, got 0
  *  test case 0 failed: expected 10, got 5
  *  test case 2 failed: expected 2, got 0
  */

int maxProfit(int k, const int *prices, int pricesSize)
{
    if (prices == NULL || pricesSize < 2 || k < 1)
    {
        return 0;
    }

    if (k >= pricesSize / 2)
    {
        long long profit = 0;
        for (int i = 1; i < pricesSize; i++)
        {
            long long diff = (long long)prices[i] - (long long)prices[i - 1];
            if (diff > 0)
            {
                profit += diff;
            }
        }
        return (int)profit;
    }

    long long *buy = (long long *)malloc(((size_t)k + 1u) * sizeof(long long));
    if (buy == NULL)
    {
        return -1;
    }

    long long *sell = (long long *)malloc(((size_t)k + 1u) * sizeof(long long));
    if (sell == NULL)
    {
        free(buy);
        buy = NULL;
        return -1;
    }

    for (int j = 0; j <= k; j++)
    {
        buy[j] = LLONG_MIN / 2;
        sell[j] = 0;
    }

    for (int i = 0; i < pricesSize; i++)
    {
        for (int j = 1; j <= k; j++)
        {
            buy[j] = llmax(buy[j], sell[j - 1] - (long long)prices[i]);
            sell[j] = llmax(sell[j], buy[j] + (long long)prices[i]);
        }
    }

    long long result = sell[k];

    free(buy);
    buy = NULL;
    free(sell);
    sell = NULL;

    return (int)result;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000002,sig:06,src:000000,time:41786,execs:17856,op:havoc,rep:3; likely memory-safety defect
  */

int main(void)
{
    size_t capacity = 16;
    size_t count = 0;
    long long *values = (long long *)malloc(capacity * sizeof(long long));
    if (values == NULL)
    {
        return EXIT_FAILURE;
    }

    int ch = 0;
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != EOF)
    {
        if (ch == '-' || isdigit((unsigned char)ch))
        {
            int sign = 1;
            if (ch == '-')
            {
                /* Possible weaknesses found:
                 * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                int next = getchar();
                if (next == EOF || !isdigit((unsigned char)next))
                {
                    if (next != EOF)
                    {
                        ungetc(next, stdin);
                    }
                    continue;
                }
                sign = -1;
                ch = next;
            }

            long long value = 0;
            while (ch != EOF && isdigit((unsigned char)ch))
            {
                /* Possible weaknesses found:
                 * UBSan: signed integer overflow: 7777777777777777777 * 10 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000000,time:25616,execs:10971,op:havoc,rep:3)
                 * UBSan: signed integer overflow: 4444444444344444444 * 10 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:3359,execs:1658,op:havoc,rep:2)
                 */
                value = value * 10 + (long long)(ch - '0');
                /* Possible weaknesses found:
                 * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = getchar();
            }
            if (ch != EOF)
            {
                ungetc(ch, stdin);
            }

            if (count == capacity)
            {
                capacity *= 2;
                long long *grown = (long long *)realloc(values, capacity * sizeof(long long));
                if (grown == NULL)
                {
                    free(values);
                    values = NULL;
                    return EXIT_FAILURE;
                }
                values = grown;
            }
            values[count++] = (long long)sign * value;
        }
    }

    if (count < 1)
    {
        free(values);
        values = NULL;
        return EXIT_FAILURE;
    }

    long long kValue = values[0];
    size_t n = count - 1;

    if (kValue < 0 || kValue > INT_MAX || n > (size_t)INT_MAX)
    {
        free(values);
        values = NULL;
        return EXIT_FAILURE;
    }

    int *prices = NULL;
    if (n > 0)
    {
        prices = (int *)malloc(n * sizeof(int));
        if (prices == NULL)
        {
            free(values);
            values = NULL;
            return EXIT_FAILURE;
        }
        for (size_t i = 0; i < n; i++)
        {
            prices[i] = (int)values[i + 1];
        }
    }

    free(values);
    values = NULL;

    int profit = maxProfit((int)kValue, prices, (int)n);
    if (profit < 0)
    {
        free(prices);
        prices = NULL;
        return EXIT_FAILURE;
    }

    printf("%d\n", profit);

    free(prices);
    prices = NULL;

    return EXIT_SUCCESS;
}