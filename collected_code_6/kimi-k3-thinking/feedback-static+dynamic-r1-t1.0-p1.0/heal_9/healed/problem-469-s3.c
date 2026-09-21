#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <stdint.h>
#include <errno.h>

int maxProfit(const int *prices, int n)
{
    long long profit = 0;

    if (prices == NULL || n <= 1)
    {
        return 0;
    }

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

static int readAllInput(char **bufferOut, size_t *lengthOut)
{
    size_t capacity = 4096U;
    size_t length = 0U;
    char *buffer = (char *)malloc(capacity);

    if (buffer == NULL)
    {
        return -1;
    }

    for (;;)
    {
        size_t space;
        size_t received;

        if (length + 1U >= capacity)
        {
            size_t newCapacity;
            char *grown;

            if (capacity > SIZE_MAX / 2U)
            {
                free(buffer);
                return -1;
            }

            newCapacity = capacity * 2U;
            grown = (char *)realloc(buffer, newCapacity);

            if (grown == NULL)
            {
                free(buffer);
                return -1;
            }

            buffer = grown;
            capacity = newCapacity;
        }

        space = capacity - length - 1U;
        received = fread(buffer + length, 1U, space, stdin);
        length += received;

        if (received < space)
        {
            if (ferror(stdin) != 0)
            {
                free(buffer);
                return -1;
            }

            break;
        }
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
        int numberStart = 0;

        if (isdigit((unsigned char)buffer[pos]) != 0)
        {
            numberStart = 1;
        }
        else if ((buffer[pos] == '-' || buffer[pos] == '+') &&
                 pos + 1U < length &&
                 isdigit((unsigned char)buffer[pos + 1U]) != 0)
        {
            numberStart = 1;
        }

        if (numberStart != 0)
        {
            char *end = NULL;
            long value;

            errno = 0;
            value = strtol(buffer + pos, &end, 10);

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
    int result;

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

    free(buffer);
    buffer = NULL;

    if (count > (size_t)INT_MAX)
    {
        fprintf(stderr, "Error: input too large.\n");
        free(values);
        return EXIT_FAILURE;
    }

    result = maxProfit(values, (int)count);

    free(values);
    values = NULL;

    printf("%d\n", result);

    return EXIT_SUCCESS;
}