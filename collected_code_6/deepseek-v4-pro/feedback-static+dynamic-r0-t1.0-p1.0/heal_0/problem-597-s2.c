#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int findKthElement(int arr1[], int n, int arr2[], int m, int k) {
    if (k < 1 || k > n + m) {
        return INT_MIN;
    }

    if (n > m) {
        return findKthElement(arr2, m, arr1, n, k);
    }

    if (n == 0) {
        return arr2[k - 1];
    }

    if (m == 0) {
        return arr1[k - 1];
    }

    int low = 0;
    int high = n < k ? n : k;

    while (low <= high) {
        int mid1 = low + (high - low) / 2;
        int mid2 = k - mid1;

        if (mid2 > m) {
            low = mid1 + 1;
            continue;
        }

        if (mid2 < 0) {
            high = mid1 - 1;
            continue;
        }

        int l1 = (mid1 == 0) ? INT_MIN : arr1[mid1 - 1];
        int l2 = (mid2 == 0) ? INT_MIN : arr2[mid2 - 1];
        int r1 = (mid1 == n) ? INT_MAX : arr1[mid1];
        int r2 = (mid2 == m) ? INT_MAX : arr2[mid2];

        if (l1 <= r2 && l2 <= r1) {
            return l1 > l2 ? l1 : l2;
        } else if (l1 > r2) {
            high = mid1 - 1;
        } else {
            low = mid1 + 1;
        }
    }

    return INT_MIN;
}

int main(void) {
    int arr1[] = {2, 3, 6, 7, 9};
    int arr2[] = {1, 4, 8, 10};
    int n = sizeof(arr1) / sizeof(arr1[0]);
    int m = sizeof(arr2) / sizeof(arr2[0]);

    int k = 5;
    int result = findKthElement(arr1, n, arr2, m, k);

    if (result != INT_MIN) {
        printf("%d\n", result);
    } else {
        printf("Invalid input\n");
    }

    int arr3[] = {1, 3, 5, 7};
    int arr4[] = {2, 4, 6, 8, 10, 12};
    int n2 = sizeof(arr3) / sizeof(arr3[0]);
    int m2 = sizeof(arr4) / sizeof(arr4[0]);

    int k2 = 7;
    int result2 = findKthElement(arr3, n2, arr4, m2, k2);

    if (result2 != INT_MIN) {
        printf("%d\n", result2);
    } else {
        printf("Invalid input\n");
    }

    return 0;
}