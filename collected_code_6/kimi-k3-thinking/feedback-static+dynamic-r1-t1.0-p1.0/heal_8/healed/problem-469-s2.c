#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <stdint.h>

static long long llmax(long long a, long long b)
{
    return (a > b) ? a : b;
}

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
                    return INT_MAX;
                }
            }
        }
        return (int)profit;
    }

    size_t slots = (size_t)k + 1u;
    if (slots > SIZE_MAX / sizeof(long long))
    {
        return -1;
    }

    long long *buy = (long long *)malloc(slots * sizeof(long long));
    long long *sell = (long long *)malloc(slots * sizeof(long long));
    if (buy == NULL || sell == NULL)
    {
        free(buy);
        free(sell);
        return -1;
    }

    for (int j = 0; j <= k; j++)
    {
        buy[j] = LLONG_MIN / 2;
        sell[j] = 0;
    }

    for (int i = 0; i < pricesSize; i++)
    {
        long long price = (long long)prices[i];
        for (int j = 1; j <= k; j++)
        {
            buy[j] = llmax(buy[j], sell[j - 1] - price);
            sell[j] = llmax(sell[j], buy[j] + price);
        }
    }

    long long result = sell[k];

    free(buy);
    free(sell);

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
        size_t newCapacity = (*capacity == 0u) ? 16u : (*capacity * 2u);
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

static int readValues(long long **outValues, size_t *outCount)
{
    size_t capacity = 16u;
    size_t count = 0u;
    long long *values = (long long *)malloc(capacity * sizeof(long long));
    if (values == NULL)
    {
        return -1;
    }

    unsigned long long magnitude = 0;
    int negative = 0;
    int inNumber = 0;
    int pendingMinus = 0;
    int overflow = 0;
    int c;

    while ((c = getchar()) != EOF)
    {
        if (isdigit((unsigned char)c))
        {
            if (!inNumber)
            {
                inNumber = 1;
                magnitude = 0;
                overflow = 0;
                negative = pendingMinus;
            }
            pendingMinus = 0;
            unsigned long long digit = (unsigned long long)(c - '0');
            unsigned long long limit = negative ? ((unsigned long long)LLONG_MAX + 1ull) : (unsigned long long)LLONG_MAX;
            if (overflow || magnitude > (limit - digit) / 10ull)
            {
                overflow = 1;
            }
            else
            {
                magnitude = magnitude * 10ull + digit;
            }
        }
        else
        {
            if (inNumber)
            {
                inNumber = 0;
                if (overflow)
                {
                    free(values);
                    return -1;
                }
                long long signedValue;
                if (negative)
                {
                    signedValue = (magnitude == (unsigned long long)LLONG_MAX + 1ull) ? LLONG_MIN : -(long long)magnitude;
                }
                else
                {
                    signedValue = (long long)magnitude;
                }
                if (appendValue(&values, &count, &capacity, signedValue) != 0)
                {
                    free(values);
                    return -1;
                }
            }
            pendingMinus = (c == '-') ? 1 : 0;
        }
    }

    if (inNumber)
    {
        if (overflow)
        {
            free(values);
            return -1;
        }
        long long signedValue;
        if (negative)
        {
            signedValue = (magnitude == (unsigned long long)LLONG_MAX + 1ull) ? LLONG_MIN : -(long long)magnitude;
        }
        else
        {
            signedValue = (long long)magnitude;
        }
        if (appendValue(&values, &count, &capacity, signedValue) != 0)
        {
            free(values);
            return -1;
        }
    }

    *outValues = values;
    *outCount = count;
    return 0;
}

int main(void)
{
    long long *values = NULL;
    size_t count = 0u;

    if (readValues(&values, &count) != 0)
    {
        return EXIT_FAILURE;
    }

    if (count < 1u)
    {
        free(values);
        return EXIT_FAILURE;
    }

    long long kValue = values[0];
    size_t n = count - 1u;

    if (kValue < 0 || kValue > (long long)INT_MAX || n > (size_t)INT_MAX || n > SIZE_MAX / sizeof(int))
    {
        free(values);
        return EXIT_FAILURE;
    }

    int *prices = NULL;
    if (n > 0u)
    {
        prices = (int *)malloc(n * sizeof(int));
        if (prices == NULL)
        {
            free(values);
            return EXIT_FAILURE;
        }
        for (size_t i = 0u; i < n; i++)
        {
            if (values[i + 1u] < (long long)INT_MIN || values[i + 1u] > (long long)INT_MAX)
            {
                free(values);
                free(prices);
                return EXIT_FAILURE;
            }
            prices[i] = (int)values[i + 1u];
        }
    }

    free(values);

    int profit = maxProfit((int)kValue, prices, (int)n);

    free(prices);

    if (profit < 0)
    {
        return EXIT_FAILURE;
    }

    printf("%d\n", profit);

    return EXIT_SUCCESS;
}