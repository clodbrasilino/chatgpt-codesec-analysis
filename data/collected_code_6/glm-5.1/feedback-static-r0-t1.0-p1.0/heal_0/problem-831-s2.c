#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    long long diff = (long long)(*(const int *)a) - (long long)(*(const int *)b);
    if (diff < 0) return -1;
    if (diff > 0) return 1;
    return 0;
}

long long count_equal_pairs(int *arr, size_t n) {
    if (n < 2) {
        return 0;
    }

    int *sorted = malloc(n * sizeof(int));
    if (!sorted) {
        return 0;
    }

    for (size_t i = 0; i < n; ++i) {
        sorted[i] = arr[i];
    }

    qsort(sorted, n, sizeof(int), compare);

    long long count = 0;
    size_t i = 0;
    while (i < n) {
        size_t j = i + 1;
        while (j < n && sorted[j] == sorted[i]) {
            j++;
        }
        long long freq = j - i;
        count += freq * (freq - 1) / 2;
        i = j;
    }

    free(sorted);
    return count;
}

int main(void) {
    int arr[] = {1, 5, 2, 1, 5, 1, 3};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    long long result = count_equal_pairs(arr, n);
    printf("%lld\n", result);

    return 0;
}