#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int find_median(const int *arr, int n) {
    if (n % 2 == 0) {
        return (arr[n / 2 - 1] + arr[n / 2]) / 2;
    }
    return arr[n / 2];
}

int median_of_two_sorted_arrays(const int *arr1, const int *arr2, int n) {
    if (n <= 0) {
        return 0;
    }
    if (n == 1) {
        return (arr1[0] + arr2[0]) / 2;
    }
    if (n == 2) {
        return (max(arr1[0], arr2[0]) + min(arr1[1], arr2[1])) / 2;
    }

    int m1 = find_median(arr1, n);
    int m2 = find_median(arr2, n);

    if (m1 == m2) {
        return m1;
    }

    int new_n;
    const int *new_arr1, *new_arr2;

    if (m1 < m2) {
        if (n % 2 == 0) {
            new_n = n - (n / 2 - 1);
            new_arr1 = arr1 + (n / 2 - 1);
            new_arr2 = arr2;
        } else {
            new_n = n - (n / 2);
            new_arr1 = arr1 + (n / 2);
            new_arr2 = arr2;
        }
    } else {
        if (n % 2 == 0) {
            new_n = n - (n / 2 - 1);
            new_arr1 = arr1;
            new_arr2 = arr2 + (n / 2 - 1);
        } else {
            new_n = n - (n / 2);
            new_arr1 = arr1;
            new_arr2 = arr2 + (n / 2);
        }
    }

    return median_of_two_sorted_arrays(new_arr1, new_arr2, new_n);
}

int main(void) {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {6, 7, 8, 9, 10};
    int n = 5;

    if (sizeof(arr2) / sizeof(arr2[0]) == n) {
        int median = median_of_two_sorted_arrays(arr1, arr2, n);
        printf("%d\n", median);
    }

    return 0;
}