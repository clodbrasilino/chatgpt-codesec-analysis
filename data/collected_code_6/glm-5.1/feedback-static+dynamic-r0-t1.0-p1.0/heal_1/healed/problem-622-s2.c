#include <stdio.h>
#include <stdlib.h>

int find_median_single(const int arr[], int n) {
    if (n % 2 == 0) {
        return (arr[n / 2 - 1] + arr[n / 2]) / 2;
    }
    return arr[n / 2];
}

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int find_median_sorted_arrays(const int arr1[], const int arr2[], int n) {
    if (n <= 0) return -1;
    if (n == 1) return (arr1[0] + arr2[0]) / 2;
    if (n == 2) return (max(arr1[0], arr2[0]) + min(arr1[1], arr2[1])) / 2;

    int m1 = find_median_single(arr1, n);
    int m2 = find_median_single(arr2, n);

    if (m1 == m2) return m1;

    if (m1 < m2) {
        if (n % 2 == 0) {
            return find_median_sorted_arrays(arr1 + n / 2 - 1, arr2, n - n / 2 + 1);
        }
        return find_median_sorted_arrays(arr1 + n / 2, arr2, n - n / 2);
    }

    if (n % 2 == 0) {
        return find_median_sorted_arrays(arr2 + n / 2 - 1, arr1, n - n / 2 + 1);
    }
    return find_median_sorted_arrays(arr2 + n / 2, arr1, n - n / 2);
}

int main() {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {6, 7, 8, 9, 10};
    int n = sizeof(arr1) / sizeof(arr1[0]);

    int median = find_median_sorted_arrays(arr1, arr2, n);

    printf("%d\n", median);

    return 0;
}