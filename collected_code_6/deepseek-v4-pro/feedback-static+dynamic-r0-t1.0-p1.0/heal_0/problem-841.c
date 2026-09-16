#include <stdio.h>
#include <stdlib.h>

long long merge_and_count(int arr[], int temp[], int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;
    long long inv_count = 0;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            inv_count += (mid - i + 1);
        }
    }

    while (i <= mid)
        temp[k++] = arr[i++];

    while (j <= right)
        temp[k++] = arr[j++];

    for (i = left; i <= right; i++)
        arr[i] = temp[i];

    return inv_count;
}

long long merge_sort_and_count(int arr[], int temp[], int left, int right) {
    long long inv_count = 0;
    if (left < right) {
        int mid = left + (right - left) / 2;
        inv_count += merge_sort_and_count(arr, temp, left, mid);
        inv_count += merge_sort_and_count(arr, temp, mid + 1, right);
        inv_count += merge_and_count(arr, temp, left, mid, right);
    }
    return inv_count;
}

long long count_inversions(int arr[], int size) {
    if (size < 2)
        return 0;
    int *temp = (int *)malloc(size * sizeof(int));
    if (temp == NULL)
        return -1;
    long long result = merge_sort_and_count(arr, temp, 0, size - 1);
    free(temp);
    return result;
}

int main(void) {
    int arr[] = {8, 4, 2, 1};
    int size = sizeof(arr) / sizeof(arr[0]);
    long long inversions = count_inversions(arr, size);
    if (inversions >= 0)
        printf("Number of inversions: %lld\n", inversions);
    else
        printf("Memory allocation failed\n");
    return 0;
}