#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static void min_heap_push(int *heap, size_t *size, int value)
{
    size_t index = (*size)++;

    heap[index] = value;

    while (index > 0U) {
        size_t parent = (index - 1U) / 2U;

        if (heap[parent] <= heap[index]) {
            break;
        }

        int temp = heap[parent];
        heap[parent] = heap[index];
        heap[index] = temp;
        index = parent;
    }
}

static void max_heap_push(int *heap, size_t *size, int value)
{
    size_t index = (*size)++;

    heap[index] = value;

    while (index > 0U) {
        size_t parent = (index - 1U) / 2U;

        if (heap[parent] >= heap[index]) {
            break;
        }

        int temp = heap[parent];
        heap[parent] = heap[index];
        heap[index] = temp;
        index = parent;
    }
}

static void min_heapify_down(int *heap, size_t size)
{
    size_t index = 0U;

    for (;;) {
        size_t left = (2U * index) + 1U;
        size_t right = left + 1U;
        size_t smallest = index;

        if (left < size && heap[left] < heap[smallest]) {
            smallest = left;
        }

        if (right < size && heap[right] < heap[smallest]) {
            smallest = right;
        }

        if (smallest == index) {
            break;
        }

        int temp = heap[index];
        heap[index] = heap[smallest];
        heap[smallest] = temp;
        index = smallest;
    }
}

static void max_heapify_down(int *heap, size_t size)
{
    size_t index = 0U;

    for (;;) {
        size_t left = (2U * index) + 1U;
        size_t right = left + 1U;
        size_t largest = index;

        if (left < size && heap[left] > heap[largest]) {
            largest = left;
        }

        if (right < size && heap[right] > heap[largest]) {
            largest = right;
        }

        if (largest == index) {
            break;
        }

        int temp = heap[index];
        heap[index] = heap[largest];
        heap[largest] = temp;
        index = largest;
    }
}

static void retain_three_largest(int heap[3], size_t *size, int value)
{
    if (*size < 3U) {
        min_heap_push(heap, size, value);
    } else if (value > heap[0]) {
        heap[0] = value;
        min_heapify_down(heap, *size);
    }
}

static void retain_two_smallest(int heap[2], size_t *size, int value)
{
    if (*size < 2U) {
        max_heap_push(heap, size, value);
    } else if (value < heap[0]) {
        heap[0] = value;
        max_heapify_down(heap, *size);
    }
}

static int maximum_product_of_three(const int *array, size_t length,
                                    int64_t *result)
{
    int largest[3];
    int smallest[2];
    size_t largest_size = 0U;
    size_t smallest_size = 0U;

    if (array == NULL || result == NULL || length < 3U) {
        return 0;
    }

    for (size_t i = 0U; i < length; ++i) {
        retain_three_largest(largest, &largest_size, array[i]);
        retain_two_smallest(smallest, &smallest_size, array[i]);
    }

    int64_t product_largest =
        (int64_t)largest[0] * largest[1] * largest[2];
    int64_t product_smallest =
        (int64_t)largest[0] * smallest[0] * smallest[1];

    *result = product_largest > product_smallest
                  ? product_largest
                  : product_smallest;

    return 1;
}

int main(void)
{
    size_t length;
    int *array = NULL;
    int64_t result;

    if (scanf("%zu", &length) != 1 || length < 3U ||
        length > SIZE_MAX / sizeof(*array)) {
        return EXIT_FAILURE;
    }

    array = malloc(length * sizeof(*array));
    if (array == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (scanf("%d", &array[i]) != 1) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (!maximum_product_of_three(array, length, &result)) {
        free(array);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);
    return EXIT_SUCCESS;
}