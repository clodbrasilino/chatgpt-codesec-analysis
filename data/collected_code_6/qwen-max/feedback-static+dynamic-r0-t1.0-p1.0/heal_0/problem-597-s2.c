#include <stdio.h>
#include <stdlib.h>

int findKth(int* arr1, int l1, int* arr2, int l2, int k) {
    if (l1 > l2) return findKth(arr2, l2, arr1, l1, k);
    if (l1 == 0) return arr2[k - 1];
    if (k == 1) return (arr1[0] < arr2[0]) ? arr1[0] : arr2[0];

    int idx1 = (l1 < k / 2) ? l1 : k / 2;
    int idx2 = k - idx1;

    if (arr1[idx1 - 1] < arr2[idx2 - 1]) {
        return findKth(arr1 + idx1, l1 - idx1, arr2, l2, k - idx1);
    } else if (arr1[idx1 - 1] > arr2[idx2 - 1]) {
        return findKth(arr1, l1, arr2 + idx2, l2 - idx2, k - idx2);
    } else {
        return arr1[idx1 - 1];
    }
}

int main() {
    int arr1[] = {2, 3, 6, 7, 9};
    int arr2[] = {1, 4, 8, 10};
    int l1 = sizeof(arr1) / sizeof(arr1[0]);
    int l2 = sizeof(arr2) / sizeof(arr2[0]);
    int k = 5;

    int result = findKth(arr1, l1, arr2, l2, k);

    printf("The %dth element is %d\n", k, result);
    return 0;
}