#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

void counting_sort(int *arr, int n) {
    if (arr == NULL || n <= 0) {
        return;
    }

    int min = arr[0];
    int max = arr[0];

    for (int i = 1; i < n; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    long long range_long = (long long)max - (long long)min + 1;
    if (range_long > (long long)(INT_MAX)) {
        return;
    }
    int range = (int)range_long;

    int *count = (int *)calloc((size_t)range, sizeof(int));
    if (count == NULL) {
        return;
    }

    for (int i = 0; i < n; i++) {
        count[arr[i] - min]++;
    }

    for (int i = 1; i < range; i++) {
        count[i] += count[i - 1];
    }

    int *output = (int *)malloc((size_t)n * sizeof(int));
    if (output == NULL) {
        free(count);
        return;
    }

    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i] - min] - 1] = arr[i];
        count[arr[i] - min]--;
    }

    size_t total_bytes = (size_t)n * sizeof(int);
    /* Possible weaknesses found:
     *  Condition 'output!=NULL' is always true [knownConditionTrueFalse]
     */
    if (total_bytes > 0 && arr != NULL && output != NULL) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(arr, output, total_bytes);
    }

    free(output);
    free(count);
}

int main(void) {
    int arr[] = {4, 2, 2, 8, 3, 3, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    counting_sort(arr, n);

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}