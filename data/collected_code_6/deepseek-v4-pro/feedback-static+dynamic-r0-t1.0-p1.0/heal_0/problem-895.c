#include <stdio.h>
#include <stdlib.h>

int maxSumNoAdjacent(int *arr, int n) {
    if (n <= 0) return 0;
    if (n == 1) return arr[0] > 0 ? arr[0] : 0;

    int incl = arr[0] > 0 ? arr[0] : 0;
    int excl = 0;
    int excl_new;

    for (int i = 1; i < n; i++) {
        excl_new = incl > excl ? incl : excl;
        incl = excl + arr[i];
        if (incl < 0) incl = 0;
        excl = excl_new;
    }

    return incl > excl ? incl : excl;
}

int main(void) {
    int arr1[] = {5, 5, 10, 100, 10, 5};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%d\n", maxSumNoAdjacent(arr1, n1));

    int arr2[] = {3, 2, 7, 10};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%d\n", maxSumNoAdjacent(arr2, n2));

    int arr3[] = {3, 2, 5, 10, 7};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("%d\n", maxSumNoAdjacent(arr3, n3));

    int arr4[] = {-2, -3, -1, -5};
    int n4 = sizeof(arr4) / sizeof(arr4[0]);
    printf("%d\n", maxSumNoAdjacent(arr4, n4));

    int arr5[] = {5, -1, 4, -3, 2};
    int n5 = sizeof(arr5) / sizeof(arr5[0]);
    printf("%d\n", maxSumNoAdjacent(arr5, n5));

    return 0;
}