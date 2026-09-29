#include <stdio.h>
#include <stdlib.h>

static void swap_int(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

static void sift_down(int *heap, size_t size, size_t root)
{
    for (;;) {
        size_t largest = root;
        size_t left = 2u * root + 1u;
        size_t right = 2u * root + 2u;

        if (left < size && heap[left] > heap[largest]) {
            largest = left;
        }
        if (right < size && heap[right] > heap[largest]) {
            largest = right;
        }
        if (largest == root) {
            break;
        }
        swap_int(&heap[root], &heap[largest]);
        root = largest;
    }
}

static void build_max_heap(int *heap, size_t size)
{
    size_t i;

    if (size < 2u) {
        return;
    }
    i = size / 2u;
    while (i > 0u) {
        i--;
        sift_down(heap, size, i);
    }
}

static int heap_n_largest(const int *numbers, size_t count, size_t n, int *result)
{
    int *heap;
    size_t heap_size;
    size_t i;

    if (numbers == NULL || result == NULL || count == 0u || n == 0u || n > count) {
        return -1;
    }
    if (count > SIZE_MAX / sizeof(int)) {
        return -1;
    }

    heap = malloc(count * sizeof(int));
    if (heap == NULL) {
        return -1;
    }

    for (i = 0u; i < count; i++) {
        heap[i] = numbers[i];
    }

    build_max_heap(heap, count);
    heap_size = count;

    for (i = 0u; i < n; i++) {
        result[i] = heap[0];
        heap_size--;
        heap[0] = heap[heap_size];
        sift_down(heap, heap_size, 0u);
    }

    free(heap);
    return 0;
}

int main(void)
{
    int numbers[] = {25, 35, 22, 85, 14, 65, 75, 22, 58};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    size_t n = 3u;
    int *result;
    size_t i;

    result = malloc(n * sizeof(int));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (heap_n_largest(numbers, count, n, result) != 0) {
        fprintf(stderr, "Failed to compute largest elements\n");
        free(result);
        return EXIT_FAILURE;
    }

    printf("The %zu largest numbers are:", n);
    for (i = 0u; i < n; i++) {
        printf(" %d", result[i]);
    }
    printf("\n");

    free(result);
    return EXIT_SUCCESS;
}