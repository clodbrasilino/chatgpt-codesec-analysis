#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

double getMedian(const int arr1[], const int arr2[], int n) {
    if (n <= 0) {
        return -1.0;
    }
    
    if (n == 1) {
        return (arr1[0] + arr2[0]) / 2.0;
    }
    
    if (n == 2) {
        return (max(arr1[0], arr2[0]) + min(arr1[1], arr2[1])) / 2.0;
    }
    
    double m1 = (n % 2 != 0) ? (double)arr1[n / 2] : (arr1[n / 2 - 1] + arr1[n / 2]) / 2.0;
    double m2 = (n % 2 != 0) ? (double)arr2[n / 2] : (arr2[n / 2 - 1] + arr2[n / 2]) / 2.0;
    
    if (m1 == m2) {
        return m1;
    }
    
    if (m1 < m2) {
        if (n % 2 == 0) {
            return getMedian(arr1 + n / 2 - 1, arr2, n - n / 2 + 1);
        }
        return getMedian(arr1 + n / 2, arr2, n - n / 2);
    }
    
    if (n % 2 == 0) {
        return getMedian(arr2 + n / 2 - 1, arr1, n - n / 2 + 1);
    }
    return getMedian(arr2 + n / 2, arr1, n - n / 2);
}

int main(void) {
    int arr1[] = {1, 12, 15, 26, 38};
    int arr2[] = {2, 13, 17, 30, 45};
    int n = sizeof(arr1) / sizeof(arr1[0]);
    
    printf("Median is %f\n", getMedian(arr1, arr2, n));
    
    return 0;
}