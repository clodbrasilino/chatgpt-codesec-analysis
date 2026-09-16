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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    int arr1[] = {2, 3, 6, 7, 9};
    int arr2[] = {1, 4, 8, 10};
    int m = sizeof(arr1) / sizeof(arr1[0]);
    int n = sizeof(arr2) / sizeof(arr2[0]);
    
    int k;
    if (argc > 1) {
        k = atoi(argv[1]);
    } else {
        k = 5;
    }

    if (k < 1 || k > m + n) {
        fprintf(stderr, "Invalid value of k\n");
        return EXIT_FAILURE;
    }

    int result = findKthElement(arr1, arr2, m, n, k);
    printf("%d\n", result);

    return EXIT_SUCCESS;
}