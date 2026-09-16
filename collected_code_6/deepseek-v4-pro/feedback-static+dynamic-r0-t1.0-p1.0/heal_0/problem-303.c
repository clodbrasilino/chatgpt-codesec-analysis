#include <stdio.h>
#include <stdlib.h>

int merge_and_count(int arr[], int temp[], int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;
    int inv_count = 0;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            inv_count += (mid - i + 1);
        }
    }

    while (i <= mid) {
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

int merge_sort_and_count(int arr[], int temp[], int left, int right) {
    int inv_count = 0;
    if (left < right) {
        int mid = left + (right - left) / 2;
        inv_count += merge_sort_and_count(arr, temp, left, mid);
        inv_count += merge_sort_and_count(arr, temp, mid + 1, right);
        inv_count += merge_and_count(arr, temp, left, mid, right);
    }
    return inv_count;
}

int count_inversions(int arr[], int n) {
    int *temp = (int *)malloc(sizeof(int) * n);
    if (temp == NULL) {
        return -1;
    }
    int inv_count = merge_sort_and_count(arr, temp, 0, n - 1);
    free(temp);
    return inv_count;
}

int have_same_inversion_count(int arr1[], int arr2[], int n) {
    int *copy1 = (int *)malloc(sizeof(int) * n);
    int *copy2 = (int *)malloc(sizeof(int) * n);
    if (copy1 == NULL || copy2 == NULL) {
        free(copy1);
        free(copy2);
        return -1;
    }

    for (int i = 0; i < n; i++) {
        copy1[i] = arr1[i];
        copy2[i] = arr2[i];
    }

    int inv1 = count_inversions(copy1, n);
    int inv2 = count_inversions(copy2, n);

    free(copy1);
    free(copy2);

    if (inv1 == -1 || inv2 == -1) {
        return -1;
    }

    return inv1 == inv2 ? 1 : 0;
}

int main() {
    int arr1[] = {2, 4, 1, 3, 5};
    int arr2[] = {1, 3, 2, 5, 4};
    int n = sizeof(arr1) / sizeof(arr1[0]);

    int result = have_same_inversion_count(arr1, arr2, n);
    if (result == -1) {
        printf("Memory allocation failed\n");
    } else if (result == 1) {
        printf("Same inversion count\n");
    } else {
        printf("Different inversion count\n");
    }

    return 0;
}