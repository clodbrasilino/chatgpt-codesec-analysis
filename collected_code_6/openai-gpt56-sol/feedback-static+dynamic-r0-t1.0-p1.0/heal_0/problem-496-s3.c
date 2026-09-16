#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static void swap_ints(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

static void sift_down(int heap[], size_t size, size_t index)
{
    for (;;) {
        size_t smallest = index;
        size_t left = index * 2U + 1U;
        size_t right = left + 1U;

        if (left < size && heap[left] < heap[smallest]) {
            smallest = left;
        }

        if (right < size && heap[right] < heap[smallest]) {
            smallest = right;
        }

        if (smallest == index) {
            break;
        }

        swap_ints(&heap[index], &heap[smallest]);
        index = smallest;
    }
}

static void build_min_heap(int heap[], size_t size)
{
    for (size_t i = size / 2U; i > 0U; --i) {
        sift_down(heap, size, i - 1U);
    }
}

static int extract_min(int heap[], size_t *size, int *value)
{
    if (heap == NULL || size == NULL || value == NULL || *size == 0U) {
        return 0;
    }

    *value = heap[0];
    --(*size);

    if (*size > 0U) {
        heap[0] = heap[*size];
        sift_down(heap, *size, 0U);
    }

    return 1;
}

static int find_smallest(const int numbers[], size_t count, size_t requested,
                         int result[])
{
    int *heap = NULL;
    size_t heap_size = count;

    if ((numbers == NULL && count != 0U) ||
        (result == NULL && requested != 0U) ||
        requested > count) {
        return 0;
    }

    if (count == 0U) {
        return 1;
    }

    if (count > SIZE_MAX / sizeof(*heap)) {
        return 0;
    }

    heap = malloc(count * sizeof(*heap));
    if (heap == NULL) {
        return 0;
    }

    for (size_t i = 0U; i < count; ++i) {
        heap[i] = numbers[i];
    }

    build_min_heap(heap, heap_size);

    for (size_t i = 0U; i < requested; ++i) {
        if (!extract_min(heap, &heap_size, &result[i])) {
            free(heap);
            return 0;
        }
    }

    free(heap);
    return 1;
}

int main(void)
{
    int numbers[] = {12, 3, 5, 7, 19, -2, 8, 1, 4};
    const size_t count = sizeof(numbers) / sizeof(numbers[0]);
    const size_t requested = 4U;
    int *smallest = NULL;

    if (requested > SIZE_MAX / sizeof(*smallest)) {
        fputs("Requested size is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    smallest = malloc(requested * sizeof(*smallest));
    if (smallest == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    if (!find_smallest(numbers, count, requested, smallest)) {
        fputs("Unable to find the smallest integers.\n", stderr);
        free(smallest);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < requested; ++i) {
        if (printf("%d%s", smallest[i], i + 1U == requested ? "\n" : " ") < 0) {
            free(smallest);
            return EXIT_FAILURE;
        }
    }

    free(smallest);
    return EXIT_SUCCESS;
}