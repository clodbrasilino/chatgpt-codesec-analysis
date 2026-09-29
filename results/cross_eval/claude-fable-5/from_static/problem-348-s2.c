#include <stdio.h>
#include <stdlib.h>

static long long countHelper(const int *values, size_t valueCount,
                             int remainingLength, long long currentSum)
{
    long long total;
    size_t i;

    if (remainingLength == 0) {
        return 1LL;
    }

    total = 0LL;
    for (i = 0; i < valueCount; i++) {
        long long newSum = currentSum + (long long)values[i];
        if (newSum >= 0LL) {
            total += countHelper(values, valueCount,
                                 remainingLength - 1, newSum);
        }
    }
    return total;
}

long long countSequences(const int *values, size_t valueCount, int length)
{
    if (values == NULL || valueCount == 0 || length < 0) {
        return -1LL;
    }
    return countHelper(values, valueCount, length, 0LL);
}

int main(void)
{
    int values[] = { 1, -1 };
    size_t valueCount = sizeof(values) / sizeof(values[0]);
    int length = 4;
    long long result;

    result = countSequences(values, valueCount, length);
    if (result < 0LL) {
        fprintf(stderr, "Invalid input parameters\n");
        return EXIT_FAILURE;
    }

    if (printf("Number of valid sequences of length %d: %lld\n",
               length, result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}