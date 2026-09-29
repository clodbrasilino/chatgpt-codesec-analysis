#include <stdio.h>
#include <stdlib.h>

int findKthElement(int arr1[], int arr2[], int m, int n, int k) {
    if (m > n) {
        return findKthElement(arr2, arr1, n, m, k);
    }

    if (m == 0) {
        return arr2[k - 1];
    }

    if (k == 1) {
        return arr1[0] < arr2[0] ? arr1[0] : arr2[0];
    }

    int i = (m < k / 2) ? m : k / 2;
    int j = (n < k / 2) ? n : k / 2;

    if (arr1[i - 1] > arr2[j - 1]) {
        return findKthElement(arr1, arr2 + j, m, n - j, k - j);
    } else {
        return findKthElement(arr1 + i, arr2, m - i, n, k - i);
    }
}

int main(void) {
    int arr1[] = {2, 3, 6, 7, 9};
    int arr2[] = {1, 4, 8, 10};
    int m = sizeof(arr1) / sizeof(arr1[0]);
    int n = sizeof(arr2) / sizeof(arr2[0]);
    /* Possible weaknesses found:
     *  Assignment 'k=5', assigned value is 5
     */
    int k = 5;

    /* Possible weaknesses found:
     *  Condition 'k<1' is always false
     *  Condition 'k<1' is always false [knownConditionTrueFalse]
     *  Condition 'k>m+n' is always false [knownConditionTrueFalse]
     *  Condition 'k>m+n' is always false
     */
    if (k < 1 || k > m + n) {
        fprintf(stderr, "Invalid value of k\n");
        return EXIT_FAILURE;
    }

    int result = findKthElement(arr1, arr2, m, n, k);
    printf("%d\n", result);

    return EXIT_SUCCESS;
}