#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>

int maxProfit(int k, const int *prices, int n)
{
    int i;
    int j;
    long *buy;
    long *sell;
    long result;

    if (k <= 0 || prices == NULL || n <= 1)
    {
        return 0;
    }

    if (k >= n / 2)
    {
        long profit = 0L;

        for (i = 1; i < n; ++i)
        {
            long diff = (long)prices[i] - (long)prices[i - 1];

            if (diff > 0L)
            {
                profit += diff;
            }
        }

        if (profit > (long)INT_MAX)
        {
            profit = (long)INT_MAX;
        }

        return (int)profit;
    }

    if ((size_t)k + 1U > SIZE_MAX / sizeof(long))
    {
        return -1;
    }

    buy = (long *)malloc(((size_t)k + 1U) * sizeof(long));
    sell = (long *)malloc(((size_t)k + 1U) * sizeof(long));

    if (buy == NULL || sell == NULL)
    {
        free(buy);
        free(sell);
        return -1;
    }

    for (j = 0; j <= k; ++j)
    {
        buy[j] = LONG_MIN / 2L;
        sell[j] = 0L;
    }

    for (i = 0; i < n; ++i)
    {
        for (j = 1; j <= k; ++j)
        {
            long candidate = sell[j - 1] - (long)prices[i];

            if (candidate > buy[j])
            {
                buy[j] = candidate;
            }

            candidate = buy[j] + (long)prices[i];

            if (candidate > sell[j])
            {
                sell[j] = candidate;
            }
        }
    }

    result = sell[k];

    free(buy);
    free(sell);

    if (result < 0L)
    {
        result = 0L;
    }

    if (result > (long)INT_MAX)
    {
        result = (long)INT_MAX;
    }

    return (int)result;
}

static int readAllInput(char **bufferOut, size_t *lengthOut)
{
    size_t capacity = 1024U;
    size_t length = 0U;
    char *buffer = (char *)malloc(capacity);
    int ch;

    if (buffer == NULL)
    {
        return -1;
    }

    while ((ch = getchar()) != EOF)
    {
        if (length + 1U >= capacity)
        {
            char *grown;
            size_t newCapacity = capacity * 2U;

            if (newCapacity <= capacity)
            {
                free(buffer);
                return -1;
            }

            grown = (char *)realloc(buffer, newCapacity);

            if (grown == NULL)
            {
                free(buffer);
                return -1;
            }

            buffer = grown;
            capacity = newCapacity;
        }

        buffer[length] = (char)ch;
        ++length;
    }

    buffer[length] = '\0';
    *bufferOut = buffer;
    *lengthOut = length;

    return 0;
}

static int argsToBuffer(int argc, char **argv, char **bufferOut, size_t *lengthOut)
{
    size_t total = 1U;
    size_t length = 0U;
    char *buffer;
    int i;

    for (i = 1; i < argc; ++i)
    {
        size_t part = strlen(argv[i]);

        if (part >= SIZE_MAX - total)
        {
            return -1;
        }

        total += part + 1U;
    }

    buffer = (char *)malloc(total);

    if (buffer == NULL)
    {
        return -1;
    }

    for (i = 1; i < argc; ++i)
    {
        size_t part = strlen(argv[i]);

        memcpy(buffer + length, argv[i], part);
        length += part;
        buffer[length] = ' ';
        ++length;
    }

    buffer[length] = '\0';
    *bufferOut = buffer;
    *lengthOut = length;

    return 0;
}

static int extractIntegers(const char *buffer, size_t length, int **valuesOut, size_t *countOut)
{
    size_t capacity = 16U;
    size_t count = 0U;
    size_t pos = 0U;
    int *values = (int *)malloc(capacity * sizeof(int));

    if (values == NULL)
    {
        return -1;
    }

    while (pos < length)
    {
        int digitHere = isdigit((unsigned char)buffer[pos]) != 0;
        int negativeNumber = buffer[pos] == '-' && pos + 1U < length &&
                             isdigit((unsigned char)buffer[pos + 1U]) != 0;

        if (digitHere || negativeNumber)
        {
            char *end = NULL;
            long value = strtol(buffer + pos, &end, 10);

            if (end == buffer + pos)
            {
                ++pos;
                continue;
            }

            if (value > (long)INT_MAX)
            {
                value = (long)INT_MAX;
            }
            else if (value < (long)INT_MIN)
            {
                value = (long)INT_MIN;
            }

            if (count >= capacity)
            {
                int *grown;
                size_t newCapacity = capacity * 2U;

                if (newCapacity <= capacity || newCapacity > SIZE_MAX / sizeof(int))
                {
                    free(values);
                    return -1;
                }

                grown = (int *)realloc(values, newCapacity * sizeof(int));

                if (grown == NULL)
                {
                    free(values);
                    return -1;
                }

                values = grown;
                capacity = newCapacity;
            }

            values[count] = (int)value;
            ++count;
            pos = (size_t)(end - buffer);
        }
        else
        {
            ++pos;
        }
    }

    *valuesOut = values;
    *countOut = count;

    return 0;
}

int main(int argc, char **argv)
{
    char *buffer = NULL;
    size_t length = 0U;
    int *values = NULL;
    size_t count = 0U;
    int k;
    const int *prices;
    int n;
    int result;

    if (argc > 1)
    {
        if (argsToBuffer(argc, argv, &buffer, &length) != 0)
        {
            fprintf(stderr, "Error: memory allocation failed.\n");
            return EXIT_FAILURE;
        }
    }
    else
    {
        if (readAllInput(&buffer, &length) != 0)
        {
            fprintf(stderr, "Error: failed to read input.\n");
            return EXIT_FAILURE;
        }
    }

    if (extractIntegers(buffer, length, &values, &count) != 0)
    {
        fprintf(stderr, "Error: invalid input.\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    free(buffer);
    buffer = NULL;

    if (count == 0U && argc <= 1)
    {
        fprintf(stderr, "Error: invalid input.\n");
        free(values);
        return EXIT_FAILURE;
    }

    if (count == 0U)
    {
        free(values);
        values = NULL;

        if (readAllInput(&buffer, &length) != 0)
        {
            fprintf(stderr, "Error: failed to read input.\n");
            return EXIT_FAILURE;
        }

        if (extractIntegers(buffer, length, &values, &count) != 0)
        {
            fprintf(stderr, "Error: invalid input.\n");
            free(buffer);
            return EXIT_FAILURE;
        }

        free(buffer);
        buffer = NULL;
    }

    if (count == 0U)
    {
        fprintf(stderr, "Error: invalid input.\n");
        free(values);
        return EXIT_FAILURE;
    }

    if (count - 1U > (size_t)INT_MAX)
    {
        fprintf(stderr, "Error: too many prices.\n");
        free(values);
        return EXIT_FAILURE;
    }

    k = values[0];
    prices = values + 1;
    n = (int)(count - 1U);

    if (k < 0)
    {
        fprintf(stderr, "Error: invalid number of transactions.\n");
        free(values);
        return EXIT_FAILURE;
    }

    result = maxProfit(k, prices, n);

    free(values);
    values = NULL;

    if (result < 0)
    {
        fprintf(stderr, "Error: profit computation failed.\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", result);

    return EXIT_SUCCESS;
}