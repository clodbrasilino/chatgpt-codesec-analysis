#include <stdio.h>
#include <stdlib.h>

static long long countSequencesHelper(const int *values, size_t numValues,
                                      int length, long long prefixSum)
{
    long long total;
    size_t i;

    if (length == 0) {
        return 1LL;
    }

    total = 0LL;
    for (i = 0; i < numValues; i++) {
        long long newSum = prefixSum + (long long)values[i];
        if (newSum >= 0LL) {
            total += countSequencesHelper(values, numValues, length - 1, newSum);
        }
    }

    return total;
}

long long countSequences(const int *values, size_t numValues, int length)
{
    if (values == NULL || numValues == 0 || length < 0) {
        return 0LL;
    }

    return countSequencesHelper(values, numValues, length, 0LL);
}

int main(void)
{
    int values[] = {1, -1};
    size_t numValues = sizeof(values) / sizeof(values[0]);
    int length = 4;
    long long result;

    result = countSequences(values, numValues, length);

    if (printf("Number of valid sequences of length %d: %lld\n",
               length, result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}