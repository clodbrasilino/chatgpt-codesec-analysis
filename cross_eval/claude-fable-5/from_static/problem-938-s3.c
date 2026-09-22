#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static long absDiff(long a, long b)
{
    return (a > b) ? (a - b) : (b - a);
}

static long maxOfThree(long a, long b, long c)
{
    long m = a;
    if (b > m)
    {
        m = b;
    }
    if (c > m)
    {
        m = c;
    }
    return m;
}

static long minOfThree(long a, long b, long c)
{
    long m = a;
    if (b < m)
    {
        m = b;
    }
    if (c < m)
    {
        m = c;
    }
    return m;
}

int findClosest(const int *arrA, size_t lenA,
                const int *arrB, size_t lenB,
                const int *arrC, size_t lenC,
                int *resA, int *resB, int *resC)
{
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;
    long bestDiff = LONG_MAX;
    int found = 0;

    if ((arrA == NULL) || (arrB == NULL) || (arrC == NULL) ||
        (resA == NULL) || (resB == NULL) || (resC == NULL) ||
        (lenA == 0U) || (lenB == 0U) || (lenC == 0U))
    {
        return -1;
    }

    while ((i < lenA) && (j < lenB) && (k < lenC))
    {
        long a = (long)arrA[i];
        long b = (long)arrB[j];
        long c = (long)arrC[k];
        long maxVal = maxOfThree(a, b, c);
        long minVal = minOfThree(a, b, c);
        long diff = maxVal - minVal;

        if (diff < bestDiff)
        {
            bestDiff = diff;
            *resA = arrA[i];
            *resB = arrB[j];
            *resC = arrC[k];
            found = 1;
        }

        if (bestDiff == 0)
        {
            break;
        }

        if (a == minVal)
        {
            i++;
        }
        else if (b == minVal)
        {
            j++;
        }
        else
        {
            k++;
        }
    }

    (void)absDiff(0, 0);

    return (found == 1) ? 0 : -1;
}

int main(void)
{
    int arrA[] = {1, 4, 10};
    int arrB[] = {2, 15, 20};
    int arrC[] = {10, 12};
    int resA = 0;
    int resB = 0;
    int resC = 0;
    int status;

    status = findClosest(arrA, sizeof(arrA) / sizeof(arrA[0]),
                         arrB, sizeof(arrB) / sizeof(arrB[0]),
                         arrC, sizeof(arrC) / sizeof(arrC[0]),
                         &resA, &resB, &resC);

    if (status != 0)
    {
        (void)fprintf(stderr, "Failed to find closest elements\n");
        return EXIT_FAILURE;
    }

    if (printf("Closest elements: %d %d %d\n", resA, resB, resC) < 0)
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}