#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>

static long long llmax(long long a, long long b)
{
    return (a > b) ? a : b;
}

int maxProfit(int k, const int *prices, int pricesSize)
{
    if (k < 1 || pricesSize < 2 || prices == NULL)
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
        if (profit > INT_MAX)
        {
            profit = INT_MAX;
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
    free(sell);

    if (result > INT_MAX)
    {
        result = INT_MAX;
    }

    return (int)result;
}

static int readNumber(long long *out)
{
    int ch;

    for (;;)
    {
        ch = getchar();
        if (ch == EOF)
        {
            return 0;
        }
        if (isdigit((unsigned char)ch))
        {
            break;
        }
        if (ch == '-')
        {
            int next = getchar();
            if (next != EOF && isdigit((unsigned char)next))
            {
                long long value = 0;
                int cur = next;
                while (cur != EOF && isdigit((unsigned char)cur))
                {
                    value = value * 10 + (long long)(cur - '0');
                    cur = getchar();
                }
                if (cur != EOF)
                {
                    ungetc(cur, stdin);
                }
                *out = -value;
                return 1;
            }
            if (next != EOF)
            {
                ungetc(next, stdin);
            }
        }
    }

    long long value = 0;
    while (ch != EOF && isdigit((unsigned char)ch))
    {
        value = value * 10 + (long long)(ch - '0');
        ch = getchar();
    }
    if (ch != EOF)
    {
        ungetc(ch, stdin);
    }

    *out = value;
    return 1;
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

    long long number = 0;
    while (readNumber(&number))
    {
        if (count == capacity)
        {
            size_t newCapacity = capacity * 2u;
            if (newCapacity < capacity || newCapacity > (SIZE_MAX / sizeof(long long)))
            {
                free(values);
                return EXIT_FAILURE;
            }
            long long *grown = (long long *)realloc(values, newCapacity * sizeof(long long));
            if (grown == NULL)
            {
                free(values);
                return EXIT_FAILURE;
            }
            values = grown;
            capacity = newCapacity;
        }
        values[count++] = number;
    }

    if (count < 1)
    {
        free(values);
        return EXIT_FAILURE;
    }

    long long kValue = values[0];
    size_t n = count - 1;

    if (kValue < 0 || kValue > INT_MAX || n > (size_t)INT_MAX)
    {
        free(values);
        return EXIT_FAILURE;
    }

    int *prices = NULL;
    if (n > 0)
    {
        prices = (int *)malloc(n * sizeof(int));
        if (prices == NULL)
        {
            free(values);
            return EXIT_FAILURE;
        }
        for (size_t i = 0; i < n; i++)
        {
            if (values[i + 1] > INT_MAX)
            {
                prices[i] = INT_MAX;
            }
            else if (values[i + 1] < INT_MIN)
            {
                prices[i] = INT_MIN;
            }
            else
            {
                prices[i] = (int)values[i + 1];
            }
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