#include <stdio.h>

int getMedian(int arr1[], int arr2[], int n) {
    if (n <= 0) {
        return -1;
    } else if (n == 1) {
        return (arr1[0] + arr2[0]) / 2;
    } else if (n == 2) {
        return (max(arr1[0], arr2[0]) + min(arr1[1], arr2[1])) / 2;
    }
    
    int m1 = median(arr1, n);
    int m2 = median(arr2, n);

    if (m1 == m2)
        return m1;

    if (m1 < m2) {
        if (n % 2 == 0)
            return getMedian(arr1 + n / 2 - 1, arr2, n - n / 2 + 1);
        return getMedian(arr1 + n / 2, arr2, n - n / 2);
    }

    if (n % 2 == 0)
        return getMedian(arr2 + n / 2 - 1, arr1, n - n / 2 + 1);
    return getMedian(arr2 + n / 2, arr1, n - n / 2);
}

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int median(int arr[], int n) {
    if (n % 2 == 0)
        return (arr[n / 2] + arr[n / 2 - 1]) / 2;
    else
        return arr[n / 2];
}

int main() {
    int arr1[] = {1, 2, 3, 6};
    int arr2[] = {4, 6, 8, 10};
    int size = sizeof arr1 / sizeof(arr1[0]);
    int median = getMedian(arr1, arr2, size);

    if (median != -1) {
        printf("Median is %d", median);
    } else {
        printf("Invalid array size");
    }

    return 0;
}