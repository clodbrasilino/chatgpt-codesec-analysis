#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void swap_int(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

static void sift_down(int *heap, size_t size, size_t idx)
{
    while (1) {
        size_t smallest = idx;
        size_t left = 2U * idx + 1U;
        size_t right = 2U * idx + 2U;

        if (left < size && heap[left] < heap[smallest]) {
            smallest = left;
        }
        if (right < size && heap[right] < heap[smallest]) {
            smallest = right;
        }
        if (smallest == idx) {
            break;
        }
        swap_int(&heap[idx], &heap[smallest]);
        idx = smallest;
    }
}

static int compare_desc(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;

    if (x < y) {
        return 1;
    }
    if (x > y) {
        return -1;
    }
    return 0;
}

int *get_n_largest(const int *data, size_t data_len, size_t n, size_t *out_len)
{
    int *heap;
    size_t i;
    size_t heap_size;

    if (out_len == NULL) {
        return NULL;
    }
    *out_len = 0;

    if (data == NULL || data_len == 0 || n == 0) {
        return NULL;
    }

    if (n > data_len) {
        n = data_len;
    }

    heap = malloc(n * sizeof(*heap));
    if (heap == NULL) {
        return NULL;
    }

    heap_size = 0;
    for (i = 0; i < data_len; i++) {
        if (heap_size < n) {
            heap[heap_size] = data[i];
            heap_size++;
            if (heap_size == n) {
                size_t j = n / 2;
                while (j > 0) {
                    j--;
                    sift_down(heap, n, j);
                }
            }
        } else if (data[i] > heap[0]) {
            heap[0] = data[i];
            sift_down(heap, n, 0);
        }
    }

    if (heap_size < n) {
        size_t j = heap_size / 2;
        while (j > 0) {
            j--;
            sift_down(heap, heap_size, j);
        }
    }

    qsort(heap, heap_size, sizeof(*heap), compare_desc);
    *out_len = heap_size;
    return heap;
}

int main(void)
{
    int dataset[] = { 42, 7, 91, 15, 63, 28, 84, 3, 56, 77, 19, 100, 5 };
    size_t dataset_len = sizeof(dataset) / sizeof(dataset[0]);
    size_t n = 5;
    size_t result_len = 0;
    size_t i;
    int *result;

    result = get_n_largest(dataset, dataset_len, n, &result_len);
    if (result == NULL) {
        fprintf(stderr, "Failed to compute the %zu largest items\n", n);
        return EXIT_FAILURE;
    }

    printf("The %zu largest items:\n", result_len);
    for (i = 0; i < result_len; i++) {
        printf("%d\n", result[i]);
    }

    free(result);
    return EXIT_SUCCESS;
}