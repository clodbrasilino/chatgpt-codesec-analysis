#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp_long(const void *a, const void *b) {
    long va = *(const long *)a;
    long vb = *(const long *)b;
    if (va < vb) return -1;
    if (va > vb) return 1;
    return 0;
}

void sift_down(long *heap, size_t parent, size_t n) {
    long val = heap[parent];
    while (1) {
        size_t left = 2 * parent + 1;
        size_t right = 2 * parent + 2;
        size_t largest = parent;

        if (left < n && cmp_long(&heap[left], &val) > 0) {
            largest = left;
        }
        if (right < n && cmp_long(&heap[right], &heap[largest]) > 0) {
            largest = right;
        }
        if (largest == parent) {
            break;
        }

        heap[parent] = heap[largest];
        parent = largest;
    }
    heap[parent] = val;
}

long *get_n_smallest(const long *data, size_t data_len, size_t n) {
    if (data == NULL || n == 0) {
        return NULL;
    }

    if (n > data_len) {
        n = data_len;
    }

    long *heap = malloc(n * sizeof(long));
    if (heap == NULL) {
        return NULL;
    }

    memcpy(heap, data, n * sizeof(long));

    for (size_t i = n / 2; i-- > 0;) {
        sift_down(heap, i, n);
    }

    for (size_t i = n; i < data_len; i++) {
        if (cmp_long(&data[i], &heap[0]) < 0) {
            heap[0] = data[i];
            sift_down(heap, 0, n);
        }
    }

    qsort(heap, n, sizeof(long), cmp_long);
    return heap;
}

int main(void) {
    long dataset[] = {100, 5, -2, 42, 0, 8, 15, -10, 23, 77};
    size_t data_len = sizeof(dataset) / sizeof(dataset[0]);
    size_t n = 4;

    long *result = get_n_smallest(dataset, data_len, n);
    if (result == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < n; i++) {
        printf("%ld ", result[i]);
    }
    printf("\n");

    free(result);
    return EXIT_SUCCESS;
}