#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

double getMedian(int* arr1, int* arr2, int n) {
    if (n <= 0) {
        return -1.0;
    }
    
    if (n == 1) {
        return (arr1[0] + arr2[0]) / 2.0;
    }
    
    if (n == 2) {
        return (max(arr1[0], arr2[0]) + min(arr1[1], arr2[1])) / 2.0;
    }
    
    double m1 = 0, m2 = 0;
    
    if (n % 2 == 0) {
        m1 = (arr1[n / 2 - 1] + arr1[n / 2]) / 2.0;
        m2 = (arr2[n / 2 - 1] + arr2[n / 2]) / 2.0;
    } else {
        m1 = arr1[n / 2];
        m2 = arr2[n / 2];
    }
    
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

int main() {
    int ar1[] = {1, 12, 15, 26, 38};
    int ar2[] = {2, 13, 17, 30, 45};
    int n1 = sizeof(ar1) / sizeof(ar1[0]);
    int n2 = sizeof(ar2) / sizeof(ar2[0]);
    
    if (n1 == n2) {
        double median = getMedian(ar1, ar2, n1);
        printf("Median is %f\n", median);
    } else {
        printf("Doesn't work for arrays of unequal size\n");
    }
    
    return 0;
}