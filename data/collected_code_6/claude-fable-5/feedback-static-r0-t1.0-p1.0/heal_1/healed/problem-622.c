#include <stdio.h>
#include <stdlib.h>

double findMedianSortedArrays(const int *a, size_t na, const int *b, size_t nb);

double findMedianSortedArrays(const int *a, size_t na, const int *b, size_t nb)
{
    size_t i = 0;
    size_t j = 0;
    size_t count = 0;
    int m1 = 0;
    int m2 = 0;

    if ((a == NULL) || (b == NULL) || (na == 0U) || (na != nb)) {
        return 0.0;
    }

    for (count = 0; count <= na; count++) {
        m1 = m2;
        if (i == na) {
            m2 = b[j];
            j++;
        } else if (j == nb) {
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
    const size_t n1 = sizeof(arr1) / sizeof(arr1[0]);
    const size_t n2 = sizeof(arr2) / sizeof(arr2[0]);
    double median = 0.0;

    median = findMedianSortedArrays(arr1, n1, arr2, n2);

    if (printf("Median: %f\n", median) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}