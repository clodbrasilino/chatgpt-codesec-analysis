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
        size_t left;
        size_t right;

        if (index > (SIZE_MAX - 2U) / 2U) {
            break;
        }

        left = (2U * index) + 1U;
        right = left + 1U;

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
    size_t index = size / 2U;

    while (index > 0U) {
        --index;
        sift_down(heap, size, index);
    }
}

static int extract_min(int heap[], size_t *size, int *result)
{
    if (heap == NULL || size == NULL || result == NULL || *size == 0U) {
        return -1;
    }

    *result = heap[0];
    --(*size);

    if (*size > 0U) {
        heap[0] = heap[*size];
        sift_down(heap, *size, 0U);
    }

    return 0;
}

static int find_smallest(const int numbers[], size_t count, size_t amount,
                         int results[])
{
    int *heap;
    size_t heap_size;
    size_t i;

    if ((numbers == NULL && count != 0U) ||
        (results == NULL && amount != 0U) ||
        amount > count) {
        return -1;
    }

    if (amount == 0U) {
        return 0;
    }

    if (count > SIZE_MAX / sizeof(*heap)) {
        return -1;
    }

    heap = malloc(count * sizeof(*heap));
    if (heap == NULL) {
        return -1;
    }

    for (i = 0U; i < count; ++i) {
        heap[i] = numbers[i];
    }

    heap_size = count;
    build_min_heap(heap, heap_size);

    for (i = 0U; i < amount; ++i) {
        if (extract_min(heap, &heap_size, &results[i]) != 0) {
            free(heap);
            return -1;
        }
    }

    free(heap);
    return 0;
}

int main(void)
{
    int numbers[] = {17, 3, 11, -4, 8, 1, 25, 0, 6};
    const size_t count = sizeof(numbers) / sizeof(numbers[0]);
    const size_t amount = 4U;
    int smallest[amount];
    size_t i;

    errno = 0;

    if (find_smallest(numbers, count, amount, smallest) != 0) {
        if (errno != 0) {
            perror("find_smallest");
        } else {
            fputs("Unable to find the smallest integers.\n", stderr);
        }
        return EXIT_FAILURE;
    }

    for (i = 0U; i < amount; ++i) {
        if (printf("%d%s", smallest[i], i + 1U == amount ? "\n" : " ") < 0) {
            fputs("Output error.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}