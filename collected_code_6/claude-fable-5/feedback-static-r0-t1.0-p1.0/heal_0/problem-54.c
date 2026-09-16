#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int counting_sort(int *arr, size_t n)
{
    int min_val;
    int max_val;
    size_t range;
    size_t i;
    int *count;
    int *output;

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

    count = calloc(range, sizeof(int));
    if (count == NULL) {
        return -1;
    }

    output = malloc(n * sizeof(int));
    if (output == NULL) {
        free(count);
        return -1;
    }

    for (i = 0; i < n; i++) {
        count[(size_t)((long long)arr[i] - (long long)min_val)]++;
    }

    for (i = 1; i < range; i++) {
        count[i] += count[i - 1];
    }

    for (i = n; i > 0; i--) {
        size_t idx = (size_t)((long long)arr[i - 1] - (long long)min_val);
        output[count[idx] - 1] = arr[i - 1];
        count[idx]--;
    }

    for (i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    free(count);
    free(output);
    return 0;
}

int main(void)
{
    int arr[] = {4, 2, -3, 8, 1, 9, -5, 2, 7, 0};
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