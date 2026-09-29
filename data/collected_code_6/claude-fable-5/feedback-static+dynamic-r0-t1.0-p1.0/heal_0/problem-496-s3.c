#include <stdio.h>
#include <stdlib.h>

static void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

static void sift_down(int *heap, size_t size, size_t root)
{
    for (;;) {
        size_t smallest = root;
        size_t left = 2U * root + 1U;
        size_t right = 2U * root + 2U;

        if (left < size && heap[left] < heap[smallest]) {
            smallest = left;
        }
        if (right < size && heap[right] < heap[smallest]) {
            smallest = right;
        }
        if (smallest == root) {
            break;
        }
        swap(&heap[root], &heap[smallest]);
        root = smallest;
    }
}

static void build_min_heap(int *heap, size_t size)
{
    size_t i = size / 2U;

    while (i > 0U) {
        i--;
        sift_down(heap, size, i);
    }
}

static int heap_pop(int *heap, size_t *size, int *out)
{
    if (heap == NULL || size == NULL || out == NULL || *size == 0U) {
        return -1;
    }
    *out = heap[0];
    (*size)--;
    heap[0] = heap[*size];
    sift_down(heap, *size, 0U);
    return 0;
}

int find_smallest(const int *numbers, size_t count, size_t k, int *result)
{
    int *heap;
    size_t heap_size;
    size_t i;

    if (numbers == NULL || result == NULL || count == 0U || k == 0U || k > count) {
        return -1;
    }
    if (count > (size_t)-1 / sizeof(int)) {
        return -1;
    }

    heap = malloc(count * sizeof(int));
    if (heap == NULL) {
        return -1;
    }

    for (i = 0U; i < count; i++) {
        heap[i] = numbers[i];
    }

    heap_size = count;
    build_min_heap(heap, heap_size);

    for (i = 0U; i < k; i++) {
        if (heap_pop(heap, &heap_size, &result[i]) != 0) {
            free(heap);
            return -1;
        }
    }

    free(heap);
    return 0;
}

int main(void)
{
    int numbers[] = { 25, 35, 22, 85, 14, 65, 75, 22, 58 };
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    size_t k = 3U;
    int result[3];
    size_t i;

    if (find_smallest(numbers, count, k, result) != 0) {
        fprintf(stderr, "Error: failed to find smallest elements\n");
        return EXIT_FAILURE;
    }

    printf("The %zu smallest numbers are:", k);
    for (i = 0U; i < k; i++) {
        printf(" %d", result[i]);
    }
    printf("\n");

    return EXIT_SUCCESS;
}