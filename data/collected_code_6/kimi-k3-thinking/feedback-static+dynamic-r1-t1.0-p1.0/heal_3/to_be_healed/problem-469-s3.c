#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 10, got 5
  *  test case 1 failed: expected 7, got 0
  *  test case 2 failed: expected 2, got 0
  */

int maxProfit(int k, const int *prices, int n)
{
    if (k <= 0 || prices == NULL || n <= 1)
    {
        return 0;
    }

    if (k >= n / 2)
    {
        long long profit = 0;

        for (int i = 1; i < n; ++i)
        {
            long long diff = (long long)prices[i] - (long long)prices[i - 1];

            if (diff > 0)
            {
                profit += diff;
            }
        }

        if (profit > (long long)INT_MAX)
        {
            profit = (long long)INT_MAX;
        }

        return (int)profit;
    }

    long long *buy = (long long *)malloc(((size_t)k + 1U) * sizeof(long long));
    long long *sell = (long long *)malloc(((size_t)k + 1U) * sizeof(long long));

    if (buy == NULL || sell == NULL)
    {
        free(buy);
        free(sell);
        return -1;
    }

    for (int j = 0; j <= k; ++j)
    {
        buy[j] = -(long long)prices[0];
        sell[j] = 0;
    }

    for (int i = 1; i < n; ++i)
    {
        for (int j = 1; j <= k; ++j)
        {
            long long buyCandidate = sell[j - 1] - (long long)prices[i];

            if (buyCandidate > buy[j])
            {
                buy[j] = buyCandidate;
            }

            long long sellCandidate = buy[j] + (long long)prices[i];

            if (sellCandidate > sell[j])
            {
                sell[j] = sellCandidate;
            }
        }
    }

    long long best = sell[k];

    free(buy);
    free(sell);

    if (best < 0)
    {
        best = 0;
    }

    if (best > (long long)INT_MAX)
    {
        best = (long long)INT_MAX;
    }

    return (int)best;
}

static int readAllInput(char **bufferOut, size_t *lengthOut)
{
    size_t capacity = 1024U;
    size_t length = 0U;
    char *buffer = (char *)malloc(capacity);
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char chunk[512];

    if (buffer == NULL)
    {
        return -1;
    }

    while (fgets(chunk, (int)sizeof(chunk), stdin) != NULL)
    {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t chunkLength = strlen(chunk);

        if (length + chunkLength + 1U > capacity)
        {
            size_t newCapacity = capacity;
            char *grown;

            while (length + chunkLength + 1U > newCapacity)
            {
                if (newCapacity > SIZE_MAX / 2U)
                {
                    free(buffer);
                    return -1;
                }

                newCapacity *= 2U;
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

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(buffer + length, chunk, chunkLength);
        length += chunkLength;
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
            long value;

            errno = 0;
            value = strtol(buffer + pos, &end, 10);

            if ((errno == ERANGE && value == LONG_MAX) || value > (long)INT_MAX)
            {
                value = (long)INT_MAX;
            }
            else if ((errno == ERANGE && value == LONG_MIN) || value < (long)INT_MIN)
            {
                value = (long)INT_MIN;
            }

            if (count >= capacity)
            {
                int *grown;
                size_t newCapacity;

                if (capacity > SIZE_MAX / (2U * sizeof(int)))
                {
                    free(values);
                    return -1;
                }

                newCapacity = capacity * 2U;
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

            if (end == buffer + pos)
            {
                ++pos;
            }
            else
            {
                pos = (size_t)(end - buffer);
            }
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

    if (count - 1U > (size_t)INT_MAX)
    {
        fprintf(stderr, "Error: input too large.\n");
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