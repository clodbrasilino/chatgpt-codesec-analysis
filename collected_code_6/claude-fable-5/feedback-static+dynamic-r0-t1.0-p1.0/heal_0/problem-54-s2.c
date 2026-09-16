#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int counting_sort(int *arr, size_t n)
{
    size_t i;
    int min_val;
    int max_val;
    size_t range;
    size_t *count;
    size_t idx;
    int j;

    if (arr == NULL || n == 0) {
        return -1;
    }

    min_val = arr[0];
    max_val = arr[0];
    for (i = 1; i < n; i++) {
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }

    if ((long long)max_val - (long long)min_val >= (long long)SIZE_MAX - 1) {
        return -1;
    }

    range = (size_t)((long long)max_val - (long long)min_val + 1);

    count = calloc(range, sizeof(size_t));
    if (count == NULL) {
        return -1;
    }

    for (i = 0; i < n; i++) {
        count[(size_t)((long long)arr[i] - (long long)min_val)]++;
    }

    idx = 0;
    for (j = 0; (size_t)j < range; j++) {
        while (count[j] > 0) {
            arr[idx] = (int)((long long)j + (long long)min_val);
            idx++;
            count[j]--;
        }
    }

    free(count);
    return 0;
}

int main(void)
{
    int arr[] = {4, 2, -3, 7, 1, 9, -3, 0, 5, 2};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    size_t i;

    if (counting_sort(arr, n) != 0) {
        fprintf(stderr, "Sorting failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < n; i++) {
        if (printf("%d ", arr[i]) < 0) {
            return EXIT_FAILURE;
        }
    }
    if (printf("\n") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}