#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

static double findMedianSortedArrays(const int *a, const int *b, size_t n);

static double findMedianSortedArrays(const int *a, const int *b, size_t n)
{
    size_t i = 0;
    size_t j = 0;
    size_t count;
    int m1 = 0;
    int m2 = 0;

    if ((a == NULL) || (b == NULL) || (n == 0U)) {
        return 0.0;
    }

    for (count = 0; count <= n; count++) {
        m1 = m2;
        if (i == n) {
            m2 = b[j];
            j++;
        } else if (j == n) {
            m2 = a[i];
            i++;
        } else if (a[i] <= b[j]) {
            m2 = a[i];
            i++;
        } else {
            m2 = b[j];
            j++;
        }
    }

    return ((double)m1 + (double)m2) / 2.0;
}

int main(void)
{
    static const int arr1[] = {1, 3, 5, 7};
    static const int arr2[] = {2, 4, 6, 8};
    double median;

    _Static_assert(ARRAY_SIZE(arr1) == ARRAY_SIZE(arr2),
                   "Arrays must be of the same size");

    median = findMedianSortedArrays(arr1, arr2, ARRAY_SIZE(arr1));

    if (printf("Median: %f\n", median) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}