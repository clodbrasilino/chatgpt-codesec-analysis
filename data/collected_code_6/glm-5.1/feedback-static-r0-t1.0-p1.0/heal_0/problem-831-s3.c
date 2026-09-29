#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    long long diff = (long long)(*(const int *)a) - (long long)(*(const int *)b);
    if (diff < 0) return -1;
    if (diff > 0) return 1;
    return 0;
}

long long count_equal_pairs(int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return 0;
    }

    int *sorted = malloc(size * sizeof(int));
    if (sorted == NULL) {
        return 0;
    }

    for (size_t i = 0; i < size; i++) {
        sorted[i] = arr[i];
    }

    qsort(sorted, size, sizeof(int), compare);

    long long count = 0;
    size_t i = 0;
    while (i < size) {
        size_t j = i + 1;
        while (j < size && sorted[j] == sorted[i]) {
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
    int arr[] = {1, 5, 1, 3, 5, 5, 2, 1};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    long long result = count_equal_pairs(arr, size);
    printf("%lld\n", result);

    return 0;
}