#include <stdio.h>
#include <stdlib.h>

long long merge(int arr[], int temp[], int left, int mid, int right) {
    int i = left;
    int j = mid;
    int k = left;
    long long count = 0;

    while (i <= mid - 1 && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            count += (mid - i);
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

    return count;
}

long long merge_sort(int arr[], int temp[], int left, int right) {
    long long count = 0;
    if (left < right) {
        int mid = left + (right - left) / 2;

        count += merge_sort(arr, temp, left, mid);
        count += merge_sort(arr, temp, mid + 1, right);
        count += merge(arr, temp, left, mid + 1, right);
    }
    return count;
}

long long count_inversions(int arr[], int n) {
    if (arr == NULL || n <= 0) {
        return 0;
    }

    int *temp = (int *)malloc(n * sizeof(int));
    if (temp == NULL) {
        return -1;
    }

    long long result = merge_sort(arr, temp, 0, n - 1);

    free(temp);
    return result;
}

int main(void) {
    int arr[] = {1, 20, 6, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    long long inv_count = count_inversions(arr, n);

    if (inv_count >= 0) {
        printf("%lld\n", inv_count);
    }

    return 0;
}