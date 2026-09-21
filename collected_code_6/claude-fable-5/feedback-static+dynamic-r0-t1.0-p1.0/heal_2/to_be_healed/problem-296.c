#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static long long merge(int *arr, int *temp, size_t n, size_t left, size_t mid, size_t right)
{
    size_t i = left;
    size_t j = mid;
    size_t k = left;
    long long inv_count = 0;

    if (arr == NULL || temp == NULL || right >= n || left > mid || mid > right) {
        return -1;
    }

    while (i <= mid - 1 && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k] = arr[i];
            k++;
            i++;
        } else {
            temp[k] = arr[j];
            k++;
            j++;
            inv_count += (long long)(mid - i);
        }
    }

    while (i <= mid - 1) {
        temp[k] = arr[i];
        k++;
        i++;
    }

    while (j <= right) {
        temp[k] = arr[j];
        k++;
        j++;
    }

    if (right - left + 1 > n - left) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(&arr[left], &temp[left], (right - left + 1) * sizeof(int));

    return inv_count;
}

static long long merge_sort(int *arr, int *temp, size_t n, size_t left, size_t right)
{
    long long inv_count = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'partial' can be reduced. [variableScope]
     *  Variable 'partial' is assigned a value that is never used. [unreadVariable]
     */
    long long partial = 0;

    if (right > left) {
        size_t mid = left + (right - left) / 2;

        partial = merge_sort(arr, temp, n, left, mid);
        if (partial < 0) {
            return -1;
        }
        inv_count += partial;

        partial = merge_sort(arr, temp, n, mid + 1, right);
        if (partial < 0) {
            return -1;
        }
        inv_count += partial;

        partial = merge(arr, temp, n, left, mid + 1, right);
        if (partial < 0) {
            return -1;
        }
        inv_count += partial;
    }

    return inv_count;
}

long long count_inversions(const int *arr, size_t n)
{
    int *copy = NULL;
    int *temp = NULL;
    long long result = -1;

    if (arr == NULL || n == 0) {
        return 0;
    }

    if (n > SIZE_MAX / sizeof(int)) {
        return -1;
    }

    copy = malloc(n * sizeof(int));
    if (copy == NULL) {
        return -1;
    }

    temp = malloc(n * sizeof(int));
    if (temp == NULL) {
        free(copy);
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, arr, n * sizeof(int));

    result = merge_sort(copy, temp, n, 0, n - 1);

    free(copy);
    free(temp);

    return result;
}

int main(void)
{
    int arr[] = { 8, 4, 2, 1 };
    size_t n = sizeof(arr) / sizeof(arr[0]);
    long long inversions;

    inversions = count_inversions(arr, n);
    if (inversions < 0) {
        if (fprintf(stderr, "Error: memory allocation failed\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Number of inversions: %lld\n", inversions) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}