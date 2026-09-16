#include <stdio.h>
#include <stdlib.h>

double findMedianSortedArrays(const int *a, const int *b, size_t n);

double findMedianSortedArrays(const int *a, const int *b, size_t n)
{
    size_t i = 0;
    size_t j = 0;
    size_t count = 0;
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
    int arr1[] = {1, 3, 5, 7};
    int arr2[] = {2, 4, 6, 8};
    /* Possible weaknesses found:
     *  Assignment 'n=sizeof(arr1)/sizeof(arr1[0])', assigned value is 4
     */
    size_t n = sizeof(arr1) / sizeof(arr1[0]);
    size_t n2 = sizeof(arr2) / sizeof(arr2[0]);
    double median = 0.0;

    /* Possible weaknesses found:
     *  Condition 'n!=n2' is always false [knownConditionTrueFalse]
     *  Condition 'n!=n2' is always false
     */
    if (n != n2) {
        (void)fprintf(stderr, "Arrays must be of the same size\n");
        return EXIT_FAILURE;
    }

    median = findMedianSortedArrays(arr1, arr2, n);

    if (printf("Median: %f\n", median) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}