#include <stdio.h>
#include <stdlib.h>

int mergeAndCount(int arr[], int temp[], int left, int mid, int right) {
    int i = left, j = mid, k = left, inv_count = 0;

    while ((i <= mid - 1) && (j <= right)) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            inv_count += (mid - i);
        }
    }

    while (i <= mid - 1) {
        temp[k++] = arr[i++];
    }

    while (j <= right) {
        temp[k++] = arr[j++];
    }

    for (i = left; i <= right; i++) {
        arr[i] = temp[i];
    }

    return inv_count;
}

int mergeSortAndCount(int arr[], int temp[], int left, int right) {
    if (right > left) {
        int mid = (right + left) / 2;

        return mergeSortAndCount(arr, temp, left, mid) +
               mergeSortAndCount(arr, temp, mid + 1, right) +
               mergeAndCount(arr, temp, left, mid + 1, right);
    }
    return 0;
}

int countInversions(int arr[], int n) {
    int temp[n];
    return mergeSortAndCount(arr, temp, 0, n - 1);
}

int areInversionCountsEqual(int arr1[], int n1, int arr2[], int n2) {
    int inv_count1 = countInversions(arr1, n1);
    int inv_count2 = countInversions(arr2, n2);
    return inv_count1 == inv_count2;
}

int main() {
    int arr1[] = {1, 20, 6, 4, 5};
    int arr2[] = {1, 2, 3, 4, 5};
    int n1 = sizeof(arr1)/sizeof(arr1[0]);
    int n2 = sizeof(arr2)/sizeof(arr2[0]);

    if (areInversionCountsEqual(arr1, n1, arr2, n2)) {
        printf("Inversion counts are equal.\n");
    } else {
        printf("Inversion counts are not equal.\n");
    }

    return 0;
}