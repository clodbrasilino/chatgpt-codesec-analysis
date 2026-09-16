#include <stdio.h>
#include <limits.h>
#include <stddef.h>

int findClosestTriplet(const int arr1[], size_t n1,
                       const int arr2[], size_t n2,
                       const int arr3[], size_t n3,
                       int *res1, int *res2, int *res3)
{
    if (n1 == 0 || n2 == 0 || n3 == 0 || res1 == NULL || res2 == NULL || res3 == NULL) {
        return -1;
    }

    size_t i = 0, j = 0, k = 0;
    int best1 = arr1[0], best2 = arr2[0], best3 = arr3[0];
    long long min_diff = LLONG_MAX;

    while (i < n1 && j < n2 && k < n3) {
        int v1 = arr1[i];
        int v2 = arr2[j];
        int v3 = arr3[k];

        int min = v1 < v2 ? (v1 < v3 ? v1 : v3) : (v2 < v3 ? v2 : v3);
        int max = v1 > v2 ? (v1 > v3 ? v1 : v3) : (v2 > v3 ? v2 : v3);
        long long diff = (long long)max - min;

        if (diff < min_diff) {
            min_diff = diff;
            best1 = v1;
            best2 = v2;
            best3 = v3;
        }

        if (min == v1) {
            i++;
        } else if (min == v2) {
            j++;
        } else {
            k++;
        }
    }

    *res1 = best1;
    *res2 = best2;
    *res3 = best3;
    return 0;
}

int main(void) {
    int arr1[] = {1, 5, 10};
    int arr2[] = {4, 7, 12};
    int arr3[] = {6, 9, 15};
    size_t n1 = sizeof(arr1) / sizeof(arr1[0]);
    size_t n2 = sizeof(arr2) / sizeof(arr2[0]);
    size_t n3 = sizeof(arr3) / sizeof(arr3[0]);
    int a, b, c;

    if (findClosestTriplet(arr1, n1, arr2, n2, arr3, n3, &a, &b, &c) == 0) {
        printf("%d %d %d\n", a, b, c);
    } else {
        printf("Invalid input\n");
    }

    return 0;
}