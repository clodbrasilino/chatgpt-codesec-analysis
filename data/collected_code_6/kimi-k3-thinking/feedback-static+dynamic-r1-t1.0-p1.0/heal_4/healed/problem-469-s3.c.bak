#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int maxProfit(int k, const int *prices, int n)
{
    int i;
    int j;
    int *buy;
    int *sell;
    int result;

    if (k <= 0 || prices == NULL || n <= 1)
    {
        return 0;
    }

    if (k >= n / 2)
    {
        long profit = 0L;

        for (i = 1; i < n; ++i)
        {
            int diff = prices[i] - prices[i - 1];

            if (diff > 0)
            {
                profit += diff;
            }
        }

        return (int)profit;
    }

    buy = (int *)malloc(((size_t)k + 1U) * sizeof(int));
    sell = (int *)malloc(((size_t)k + 1U) * sizeof(int));

    if (buy == NULL || sell == NULL)
    {
        free(buy);
        free(sell);
        return -1;
    }

    for (j = 0; j <= k; ++j)
    {
        buy[j] = -prices[0];
        sell[j] = 0;
    }

    for (i = 1; i < n; ++i)
    {
        for (j = 1; j <= k; ++j)
        {
            int buyCandidate = sell[j - 1] - prices[i];

            if (buyCandidate > buy[j])
            {
                buy[j] = buyCandidate;
            }

            {
                int sellCandidate = buy[j] + prices[i];

                if (sellCandidate > sell[j])
                {
                    sell[j] = sellCandidate;
                }
            }
        }
    }

    result = sell[k];

    free(buy);
    free(sell);

    return result;
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

            capacity *= 2U;
            grown = (char *)realloc(buffer, capacity);

            if (grown == NULL)
            {
                free(buffer);
                return -1;
            }

            buffer = grown;
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
        total += strlen(argv[i]) + 1U;
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

            if (count >= capacity)
            {
                int *grown;

                capacity *= 2U;
                grown = (int *)realloc(values, capacity * sizeof(int));

                if (grown == NULL)
                {
                    free(values);
                    return -1;
                }

                values = grown;
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
    int usedArgs = 0;
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

        usedArgs = 1;
    }
    else if (readAllInput(&buffer, &length) != 0)
    {
        fprintf(stderr, "Error: failed to read input.\n");
        return EXIT_FAILURE;
    }

    if (extractIntegers(buffer, length, &values, &count) != 0)
    {
        fprintf(stderr, "Error: memory allocation failed.\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    if (count == 0U && usedArgs)
    {
        free(values);
        values = NULL;
        free(buffer);
        buffer = NULL;

        if (readAllInput(&buffer, &length) != 0)
        {
            fprintf(stderr, "Error: failed to read input.\n");
            return EXIT_FAILURE;
        }

        if (extractIntegers(buffer, length, &values, &count) != 0)
        {
            fprintf(stderr, "Error: memory allocation failed.\n");
            free(buffer);
            return EXIT_FAILURE;
        }
    }

    free(buffer);
    buffer = NULL;

    if (count == 0U)
    {
        fprintf(stderr, "Error: invalid input.\n");
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