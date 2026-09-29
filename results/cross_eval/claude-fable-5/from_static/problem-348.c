#include <stdio.h>
#include <stdlib.h>

static long long countSequencesUtil(const int *values, size_t numValues, int remaining, long long prefixSum);
static long long countSequences(const int *values, size_t numValues, int length);

static long long countSequencesUtil(const int *values, size_t numValues, int remaining, long long prefixSum)
{
    long long total;
    size_t i;

    if (prefixSum < 0)
    {
        return 0;
    }

    if (remaining == 0)
    {
        return 1;
    }

    total = 0;
    for (i = 0; i < numValues; i++)
    {
        total += countSequencesUtil(values, numValues, remaining - 1, prefixSum + values[i]);
    }

    return total;
}

static long long countSequences(const int *values, size_t numValues, int length)
{
    if (values == NULL || numValues == 0 || length < 0)
    {
        return 0;
    }

    return countSequencesUtil(values, numValues, length, 0);
}

int main(void)
{
    int values[] = { 1, -1 };
    size_t numValues;
    int length;
    long long result;

    numValues = sizeof(values) / sizeof(values[0]);
    length = 4;

    result = countSequences(values, numValues, length);

    if (printf("Number of valid sequences of length %d: %lld\n", length, result) < 0)
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}