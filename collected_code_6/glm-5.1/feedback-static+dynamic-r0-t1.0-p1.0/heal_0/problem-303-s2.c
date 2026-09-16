#include <stdio.h>
#include <stdlib.h>

long long merge_count(int arr[], int temp[], int left, int mid, int right) {
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

long long merge_sort_count(int arr[], int temp[], int left, int right) {
    long long count = 0;
    if (left < right) {
        int mid = left + (right - left) / 2;
        count += merge_sort_count(arr, temp, left, mid);
        count += merge_sort_count(arr, temp, mid + 1, right);
        count += merge_count(arr, temp, left, mid + 1, right);
    }
    return count;
}

long long count_type1_inversions(int arr[], int n) {
    int *temp = (int *)malloc(n * sizeof(int));
    if (temp == NULL) {
        return -1;
    }
    int *copy = (int *)malloc(n * sizeof(int));
    if (copy == NULL) {
        free(temp);
        return -1;
    }
    for (int i = 0; i < n; i++) {
        copy[i] = arr[i];
    }
    long long count = merge_sort_count(copy, temp, 0, n - 1);
    free(temp);
    free(copy);
    return count;
}

long long count_type2_inversions(int arr[], int n) {
    int *temp = (int *)malloc(n * sizeof(int));
    if (temp == NULL) {
        return -1;
    }
    int *copy = (int *)malloc(n * sizeof(int));
    if (copy == NULL) {
        free(temp);
        return -1;
    }
    for (int i = 0; i < n; i++) {
        copy[i] = -arr[i];
    }
    long long count = merge_sort_count(copy, temp, 0, n - 1);
    free(temp);
    free(copy);
    return count;
}

int check_inversion_counts_same(int arr[], int n) {
    if (n <= 1) {
        return 1;
    }
    long long c1 = count_type1_inversions(arr, n);
    long long c2 = count_type2_inversions(arr, n);
    if (c1 == -1 || c2 == -1) {
        return -1;
    }
    return c1 == c2;
}

int main() {
    int arr1[] = {1, 2, 3, 4, 5};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int res1 = check_inversion_counts_same(arr1, n1);
    if (res1 != -1) {
        printf("%d\n", res1);
    }

    int arr2[] = {5, 4, 3, 2, 1};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int res2 = check_inversion_counts_same(arr2, n2);
    if (res2 != -1) {
        printf("%d\n", res2);
    }

    int arr3[] = {2, 4, 1, 3, 5};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    int res3 = check_inversion_counts_same(arr3, n3);
    if (res3 != -1) {
        printf("%d\n", res3);
    }

    return 0;
}