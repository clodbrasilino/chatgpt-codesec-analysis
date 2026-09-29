#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    long long ia = *(const long long *)a;
    long long ib = *(const long long *)b;
    return (ia > ib) - (ia < ib);
}

long long calculate_unique_product(const long long *array, size_t size) {
    if (array == NULL || size == 0) {
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
    for (size_t i = 0; i < size; ++i) {
        if (i == 0 || sorted[i] != sorted[i - 1]) {
            product *= sorted[i];
        }
    }

    free(sorted);
    return product;
}

int main(void) {
    long long data[] = {2, 3, 2, 5, 4, 5, 3, 7};
    size_t count = sizeof(data) / sizeof(data[0]);

    long long result = calculate_unique_product(data, count);

    printf("%lld\n", result);

    return 0;
}