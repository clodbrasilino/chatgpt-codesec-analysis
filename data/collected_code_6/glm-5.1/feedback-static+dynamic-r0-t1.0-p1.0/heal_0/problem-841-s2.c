#include <stdio.h>
#include <stdlib.h>

long long merge_count(int *arr, int *temp, int left, int mid, int right) {
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

long long merge_sort_count(int *arr, int *temp, int left, int right) {
    long long count = 0;
    if (left < right) {
        int mid = left + (right - left) / 2;
        count += merge_sort_count(arr, temp, left, mid);
        count += merge_sort_count(arr, temp, mid + 1, right);
        count += merge_count(arr, temp, left, mid + 1, right);
    }
    return count;
}

long long count_inversions(int *arr, int n) {
    if (n <= 1) {
        return 0;
    }
    
    int *temp = (int *)malloc(n * sizeof(int));
    if (temp == NULL) {
        return -1;
    }

    long long result = merge_sort_count(arr, temp, 0, n - 1);
    
    free(temp);
    
    return result;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }

    int n = argc - 1;
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = atoi(argv[i + 1]);
    }

    long long inversions = count_inversions(arr, n);
    if (inversions >= 0) {
        printf("%lld\n", inversions);
    }

    free(arr);

    return 0;
}