#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <stdint.h>

static long long llmax(long long a, long long b)
{
    return (a > b) ? a : b;
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected 10, got 5
  *  test case 1 failed: expected 7, got 0
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
                if (profit > INT_MAX)
                {
                    profit = INT_MAX;
                }
            }
        }
        return (int)profit;
    }

    if ((size_t)k + 1u > SIZE_MAX / sizeof(long long))
    {
        return -1;
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
            if (sell[j] > INT_MAX)
            {
                sell[j] = INT_MAX;
            }
        }
    }

    long long result = sell[k];

    free(buy);
    buy = NULL;
    free(sell);
    sell = NULL;

    if (result < 0)
    {
        result = 0;
    }
    if (result > INT_MAX)
    {
        result = INT_MAX;
    }

    return (int)result;
}

static int appendValue(long long **values, size_t *count, size_t *capacity, long long v)
{
    if (*count == *capacity)
    {
        if (*capacity > SIZE_MAX / (2u * sizeof(long long)))
        {
            return -1;
        }
        size_t newCapacity = *capacity * 2u;
        long long *grown = (long long *)realloc(*values, newCapacity * sizeof(long long));
        if (grown == NULL)
        {
            return -1;
        }
        *values = grown;
        *capacity = newCapacity;
    }
    (*values)[*count] = v;
    *count += 1u;
    return 0;
}

int main(void)
{
    size_t capacity = 16;
    size_t count = 0;
    long long *values = (long long *)malloc(capacity * sizeof(long long));
    if (values == NULL)
    {
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[4096];
    long long current = 0;
    int sign = 1;
    int inNumber = 0;
    int pendingMinus = 0;
    int overflow = 0;
    int failed = 0;

    while (!failed && fgets(buffer, (int)sizeof(buffer), stdin) != NULL)
    {
        for (size_t i = 0; buffer[i] != '\0'; i++)
        {
            unsigned char c = (unsigned char)buffer[i];
            if (isdigit(c))
            {
                if (!inNumber)
                {
                    inNumber = 1;
                    current = 0;
                    overflow = 0;
                    sign = pendingMinus ? -1 : 1;
                }
                pendingMinus = 0;
                int digit = (int)(c - '0');
                if (current > (LLONG_MAX - (long long)digit) / 10)
                {
                    overflow = 1;
                }
                else
                {
                    current = current * 10 + (long long)digit;
                }
            }
            else
            {
                if (inNumber)
                {
                    inNumber = 0;
                    if (overflow)
                    {
                        failed = 1;
                        break;
                    }
                    long long signedValue = (sign < 0) ? -current : current;
                    if (appendValue(&values, &count, &capacity, signedValue) != 0)
                    {
                        failed = 1;
                        break;
                    }
                }
                pendingMinus = (c == '-') ? 1 : 0;
            }
        }
    }

    if (!failed && inNumber)
    {
        long long signedValue = (sign < 0) ? -current : current;
        if (overflow || appendValue(&values, &count, &capacity, signedValue) != 0)
        {
            failed = 1;
        }
    }

    if (failed || count < 1)
    {
        free(values);
        values = NULL;
        return EXIT_FAILURE;
    }

    long long kValue = values[0];
    size_t n = count - 1;

    if (kValue < 0 || kValue > INT_MAX || n > (size_t)INT_MAX || n > SIZE_MAX / sizeof(int))
    {
        free(values);
        values = NULL;
        return EXIT_FAILURE;
    }

    int *prices = NULL;
    if (n > 0)
    {
        for (size_t i = 0; i < n; i++)
        {
            if (values[i + 1] < (long long)INT_MIN || values[i + 1] > (long long)INT_MAX)
            {
                free(values);
                values = NULL;
                return EXIT_FAILURE;
            }
        }

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