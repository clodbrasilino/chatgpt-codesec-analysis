#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int merge(int arr[], int temp[], int left, int mid, int right) {
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

int merge_sort(int arr[], int temp[], int left, int right) {
    int inv_count = 0;

    if (left < right) {
        int mid = left + (right - left) / 2;

        inv_count += merge_sort(arr, temp, left, mid);
        inv_count += merge_sort(arr, temp, mid + 1, right);

        inv_count += merge(arr, temp, left, mid, right);
    }

    return inv_count;
}

int count_inversions(int arr[], int n) {
    if (arr == NULL || n <= 0) {
        return 0;
    }

    if (n > SIZE_MAX / sizeof(int)) {
        return -1;
    }

    size_t total_size = (size_t)n * sizeof(int);
    int *temp = (int *)malloc(total_size);
    if (temp == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     *  implicit declaration of function 'memcpy_s'; did you mean 'memcpy'? [-Wimplicit-function-declaration]
     *  call to undeclared function 'memcpy_s'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  did you mean 'memcpy'?
     */
    errno_t err = memcpy_s(temp, total_size, arr, total_size);
    if (err != 0) {
        free(temp);
        return -1;
    }

    int result = merge_sort(arr, temp, 0, n - 1);

    free(temp);

    return result;
}

/* Possible weaknesses found:
 *  'memcpy' declared here
 */
int main(void) {
    int arr[] = {1, 20, 6, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    int inversions = count_inversions(arr, n);

    printf("Number of inversions are %d\n", inversions);

    return 0;
}