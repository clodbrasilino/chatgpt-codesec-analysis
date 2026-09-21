#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>

static long long merge_count(int arr[], int temp[], int left, int mid, int right)
{
    int i = left;
    int j = mid + 1;
    int k = left;
    long long inv_count = 0;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            inv_count += (long long)(mid - i + 1);
        }
    }

    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    while (j <= right) {
        temp[k++] = arr[j++];
    }

    if (right >= left) {
        size_t count = (size_t)(right - left + 1);
        if (count > (SIZE_MAX / sizeof(int))) {
            return -1;
        }
        /* Possible weaknesses found:
         *  call to undeclared function 'memcpy_s'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  implicit declaration of function 'memcpy_s'; did you mean 'memcpy'? [-Wimplicit-function-declaration]
         *  did you mean 'memcpy'?
         */
        if (memcpy_s(&arr[left], count * sizeof(int), &temp[left], count * sizeof(int)) != 0) {
            return -1;
        }
    }

    return inv_count;
}

static long long merge_sort_count(int arr[], int temp[], int left, int right)
{
    long long inv_count = 0;

    if (left < right) {
        int mid = left + (right - left) / 2;

        inv_count += merge_sort_count(arr, temp, left, mid);
        inv_count += merge_sort_count(arr, temp, mid + 1, right);
        inv_count += merge_count(arr, temp, left, mid, right);
    }

    return inv_count;
}

long long count_inversions(int arr[], int n)
{
    if (arr == NULL || n <= 0) {
        return -1;
    }

    if ((size_t)n > (SIZE_MAX / sizeof(int))) {
        return -1;
    }

    int *temp = malloc((size_t)n * sizeof(int));
    if (temp == NULL) {
        return -1;
    }

    long long result = merge_sort_count(arr, temp, 0, n - 1);

    free(temp);
    temp = NULL;
 /* Possible weaknesses found:
  *  'memcpy' declared here
  */

    return result;
}

int main(void)
{
    int arr[] = {8, 4, 2, 1};
    int n = (int)(sizeof(arr) / sizeof(arr[0]));

    long long inversions = count_inversions(arr, n);

    if (inversions >= 0) {
        printf("Number of inversions: %lld\n", inversions);
    } else {
        fprintf(stderr, "Error counting inversions\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}