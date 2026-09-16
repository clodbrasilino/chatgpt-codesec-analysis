#include <stdio.h>
#include <stdlib.h>

long long merge_count(int arr[], int temp[], int left, int mid, int right, int (*cmp)(int, int)) {
    int i = left;
    int j = mid;
    int k = left;
    long long count = 0;

    while (i <= mid - 1 && j <= right) {
        if (cmp(arr[i], arr[j])) {
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

long long merge_sort_count(int arr[], int temp[], int left, int right, int (*cmp)(int, int)) {
    long long count = 0;
    if (left < right) {
        int mid = left + (right - left) / 2;
        count += merge_sort_count(arr, temp, left, mid, cmp);
        count += merge_sort_count(arr, temp, mid + 1, right, cmp);
        count += merge_count(arr, temp, left, mid + 1, right, cmp);
    }
    return count;
}

int cmp_ascending(int a, int b) {
    return a <= b;
}

int cmp_descending(int a, int b) {
    return a >= b;
}

int check_inversion_counts(int arr[], int n) {
    if (arr == NULL || n <= 0) {
        return 0;
    }

    int *temp = (int *)malloc(n * sizeof(int));
    if (temp == NULL) {
        return 0;
    }

    int *arr_copy = (int *)malloc(n * sizeof(int));
    if (arr_copy == NULL) {
        free(temp);
        return 0;
    }

    for (int i = 0; i < n; i++) {
        arr_copy[i] = arr[i];
    }

    long long asc_inv = merge_sort_count(arr_copy, temp, 0, n - 1, cmp_ascending);
    
    for (int i = 0; i < n; i++) {
        arr_copy[i] = arr[i];
    }
    
    long long desc_inv = merge_sort_count(arr_copy, temp, 0, n - 1, cmp_descending);

    free(temp);
    free(arr_copy);

    return asc_inv == desc_inv;
}

int main() {
    int arr1[] = {1, 3, 2};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%d\n", check_inversion_counts(arr1, n1));

    int arr2[] = {1, 2, 3};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%d\n", check_inversion_counts(arr2, n2));

    int arr3[] = {3, 2, 1};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("%d\n", check_inversion_counts(arr3, n3));

    return 0;
}