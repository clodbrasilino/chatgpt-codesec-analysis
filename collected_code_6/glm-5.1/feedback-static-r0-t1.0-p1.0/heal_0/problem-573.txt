#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    long long ia = *(const long long *)a;
    long long ib = *(const long long *)b;
    if (ia < ib) return -1;
    if (ia > ib) return 1;
    return 0;
}

long long product_of_uniques(const long long *array, size_t size) {
    if (array == NULL) {
        return 0;
    }

    if (size == 0) {
        return 0;
    }

    long long *sorted = malloc(size * sizeof(long long));
    if (sorted == NULL) {
        return 0;
    }

    for (size_t i = 0; i < size; ++i) {
        sorted[i] = array[i];
    }

    qsort(sorted, size, sizeof(long long), compare);

    long long product = 1;
    size_t i = 0;

    while (i < size) {
        long long current = sorted[i];
        size_t j = i + 1;

        while (j < size && sorted[j] == current) {
            j++;
        }

        if (j - i == 1) {
            product *= current;
        }

        i = j;
    }

    free(sorted);
    return product;
}

int main(void) {
    long long data[] = {2, 3, 2, 5, 4, 5, 7, 8, 3};
    size_t len = sizeof(data) / sizeof(data[0]);

    long long result = product_of_uniques(data, len);

    printf("%lld\n", result);

    return 0;
}