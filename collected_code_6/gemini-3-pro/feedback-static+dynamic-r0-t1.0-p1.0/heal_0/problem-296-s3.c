#include <stdio.h>
#include <stdlib.h>

long long merge_and_count(int arr[], int temp[], size_t left, size_t mid, size_t right);
long long merge_sort_and_count(int arr[], int temp[], size_t left, size_t right);
long long count_inversions(int arr[], size_t n);

long long merge_and_count(int arr[], int temp[], size_t left, size_t mid, size_t right) {
    size_t i = left;
    size_t j = mid + 1;
    size_t k = left;
    long long inv_count = 0;

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

long long merge_sort_and_count(int arr[], int temp[], size_t left, size_t right) {
    long long inv_count = 0;
    if (left < right) {
        size_t mid = left + (right - left) / 2;
        inv_count += merge_sort_and_count(arr, temp, left, mid);
        inv_count += merge_sort_and_count(arr, temp, mid + 1, right);
        inv_count += merge_and_count(arr, temp, left, mid, right);
    }
    return inv_count;
}

long long count_inversions(int arr[], size_t n) {
    if (arr == NULL || n == 0) {
        return 0;
    }

    int *temp = (int *)malloc(n * sizeof(int));
    if (temp == NULL) {
        return -1;
    }

    long long inv_count = merge_sort_and_count(arr, temp, 0, n - 1);
    free(temp);
    
    return inv_count;
}

int main(void) {
    int arr[] = {1, 20, 6, 4, 5};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    long long inversions = count_inversions(arr, n);

    if (inversions == -1) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("%lld\n", inversions);

    return EXIT_SUCCESS;
}