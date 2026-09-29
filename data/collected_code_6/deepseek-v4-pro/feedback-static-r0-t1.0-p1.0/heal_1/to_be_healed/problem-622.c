#include <stdio.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

int median(int arr[], int n) {
    if (n % 2 == 0)
        return (arr[n/2] + arr[n/2 - 1]) / 2;
    else
        return arr[n/2];
}

int findMedian(int arr1[], int arr2[], int n) {
    if (n <= 0)
        return -1;
    if (n == 1)
        return (arr1[0] + arr2[0]) / 2;
    if (n == 2)
        return (max(arr1[0], arr2[0]) + min(arr1[1], arr2[1])) / 2;

    int m1 = median(arr1, n);
    int m2 = median(arr2, n);

    if (m1 == m2)
        return m1;

    if (m1 < m2) {
        if (n % 2 == 0)
            return findMedian(arr1 + n/2 - 1, arr2, n - n/2 + 1);
        else
            return findMedian(arr1 + n/2, arr2, n - n/2);
    }

    if (n % 2 == 0)
        return findMedian(arr2 + n/2 - 1, arr1, n - n/2 + 1);
    else
        return findMedian(arr2 + n/2, arr1, n - n/2);
}

int main(void) {
    int arr1[] = {1, 12, 15, 26, 38};
    int arr2[] = {2, 13, 17, 30, 45};
    /* Possible weaknesses found:
     *  Assignment 'n=sizeof(arr1)/sizeof(arr1[0])', assigned value is 5
     */
    int n = sizeof(arr1) / sizeof(arr1[0]);

    if (sizeof(arr2) / sizeof(arr2[0]) != n) {
        printf("Arrays must be of same size\n");
        return 1;
    }

    /* Possible weaknesses found:
     *  Condition 'n<=0' is always false [knownConditionTrueFalse]
     *  Condition 'n<=0' is always false
     */
    if (n <= 0) {
        printf("Invalid array size\n");
        return 1;
    }

    printf("Median is %d\n", findMedian(arr1, arr2, n));

    return 0;
}