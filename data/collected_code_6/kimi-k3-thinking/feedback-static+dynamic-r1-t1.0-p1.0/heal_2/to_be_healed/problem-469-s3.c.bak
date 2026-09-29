#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 7, got <no output>
  *  test case 2 failed: expected 2, got <no output>
  *  test case 0 failed: expected 10, got <no output>
  */

int maxProfit(int k, const int *prices, int n)
{
    if (k <= 0 || prices == NULL || n <= 1)
    {
        return 0;
    }

    if (k >= n / 2)
    {
        int profit = 0;

        for (int i = 1; i < n; ++i)
        {
            int diff = prices[i] - prices[i - 1];

            if (diff > 0)
            {
                profit += diff;
            }
        }

        return profit;
    }

    int *buy = (int *)malloc(((size_t)k + 1U) * sizeof(int));
    int *sell = (int *)malloc(((size_t)k + 1U) * sizeof(int));

    if (buy == NULL || sell == NULL)
    {
        free(buy);
        free(sell);
        return -1;
    }

    for (int j = 0; j <= k; ++j)
    {
        buy[j] = -prices[0];
        sell[j] = 0;
    }

    for (int i = 1; i < n; ++i)
    {
        for (int j = 1; j <= k; ++j)
        {
            int buyCandidate = sell[j - 1] - prices[i];

            if (buyCandidate > buy[j])
            {
                buy[j] = buyCandidate;
            }

            int sellCandidate = buy[j] + prices[i];

            if (sellCandidate > sell[j])
            {
                sell[j] = sellCandidate;
            }
        }
    }

    int result = sell[k];

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

int main(void)
{
    char *buffer = NULL;
    size_t length = 0U;
    int *values = NULL;
    size_t count = 0U;
    int structured = 0;
    int k;
    const int *prices;
    int n;
    int result;

    if (readAllInput(&buffer, &length) != 0)
    {
        fprintf(stderr, "Error: failed to read input.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < length; ++i)
    {
        unsigned char c = (unsigned char)buffer[i];

        if (isalpha(c) != 0 || c == '[' || c == ']' || c == '=' || c == ':' || c == '{' || c == '}')
        {
            structured = 1;
            break;
        }
    }

    if (extractIntegers(buffer, length, &values, &count) != 0)
    {
        fprintf(stderr, "Error: memory allocation failed.\n");
        free(buffer);
        return EXIT_FAILURE;
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

    if (!structured && count >= 2U && values[1] >= 0 && (size_t)values[1] == count - 2U)
    {
        n = values[1];
        prices = values + 2;
    }

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