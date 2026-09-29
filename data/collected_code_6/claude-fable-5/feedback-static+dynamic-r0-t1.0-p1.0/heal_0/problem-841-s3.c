#include <stdio.h>
#include <stdlib.h>

static long long merge_count(int *arr, int *temp, size_t left, size_t mid, size_t right)
{
    size_t i = left;
    size_t j = mid;
    size_t k = left;
    long long inversions = 0;

    while (i < mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k] = arr[i];
            i++;
        } else {
            temp[k] = arr[j];
            inversions += (long long)(mid - i);
            j++;
        }
        k++;
    }

    while (i < mid) {
        temp[k] = arr[i];
        i++;
        k++;
    }

    while (j <= right) {
        temp[k] = arr[j];
        j++;
        k++;
    }

    for (i = left; i <= right; i++) {
        arr[i] = temp[i];
    }

    return inversions;
}

static long long sort_count(int *arr, int *temp, size_t left, size_t right)
{
    long long inversions = 0;

    if (left < right) {
        size_t mid = left + (right - left) / 2;
        inversions += sort_count(arr, temp, left, mid);
        inversions += sort_count(arr, temp, mid + 1, right);
        inversions += merge_count(arr, temp, left, mid + 1, right);
    }

    return inversions;
}

long long count_inversions(const int *arr, size_t n)
{
    int *copy;
    int *temp;
    long long result;
    size_t i;

    if (arr == NULL || n < 2) {
        return 0;
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

    for (i = 0; i < n; i++) {
        copy[i] = arr[i];
    }

    result = sort_count(copy, temp, 0, n - 1);

    free(copy);
    free(temp);

    return result;
}

int main(void)
{
    int data[] = {8, 4, 2, 1, 9, 3};
    size_t n = sizeof(data) / sizeof(data[0]);
    long long inversions;

    inversions = count_inversions(data, n);
    if (inversions < 0) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (printf("Number of inversions: %lld\n", inversions) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}