#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

double find_median_sorted_arrays(int *arr1, int *arr2, int n) {
    if (n <= 0) {
        return 0.0;
    }
    if (n == 1) {
        return ((double)arr1[0] + (double)arr2[0]) / 2.0;
    }
    if (n == 2) {
        return ((double)max(arr1[0], arr2[0]) + (double)min(arr1[1], arr2[1])) / 2.0;
    }

    int m1 = 0, m2 = 0;
    if (n % 2 == 0) {
        m1 = (arr1[n / 2 - 1] + arr1[n / 2]) / 2;
        m2 = (arr2[n / 2 - 1] + arr2[n / 2]) / 2;
        if (m1 == m2) {
            return (double)m1;
        }
    } else {
        m1 = arr1[n / 2];
        m2 = arr2[n / 2];
        if (m1 == m2) {
            return (double)m1;
        }
    }

    if (m1 < m2) {
        if (n % 2 == 0) {
            return find_median_sorted_arrays(arr1 + n / 2 - 1, arr2, n - n / 2 + 1);
        }
        return find_median_sorted_arrays(arr1 + n / 2, arr2, n - n / 2);
    }

    if (n % 2 == 0) {
        return find_median_sorted_arrays(arr1, arr2 + n / 2 - 1, n - n / 2 + 1);
    }
    return find_median_sorted_arrays(arr1, arr2 + n / 2, n - n / 2);
}

int main(void) {
    int arr1[] = {1, 2, 3, 6};
    int arr2[] = {4, 6, 8, 10};
    int n = sizeof(arr1) / sizeof(arr1[0]);

    double median = find_median_sorted_arrays(arr1, arr2, n);
    printf("%f\n", median);

    return 0;
}