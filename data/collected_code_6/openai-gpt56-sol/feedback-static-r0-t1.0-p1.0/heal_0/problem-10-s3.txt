#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static void swap_ints(int *a, int *b)
{
    int temporary = *a;
    *a = *b;
    *b = temporary;
}

static void sift_down_max_heap(int *heap, size_t size, size_t index)
{
    for (;;) {
        size_t largest = index;
        size_t left;
        size_t right;

        if (index > (SIZE_MAX - 1U) / 2U) {
            break;
        }

        left = index * 2U + 1U;
        right = left + 1U;

        if (left < size && heap[left] > heap[largest]) {
            largest = left;
        }

        if (right < size && heap[right] > heap[largest]) {
            largest = right;
        }

        if (largest == index) {
            break;
        }

        swap_ints(&heap[index], &heap[largest]);
        index = largest;
    }
}

static void build_max_heap(int *heap, size_t size)
{
    size_t index;

    if (size < 2U) {
        return;
    }

    index = size / 2U;
    while (index > 0U) {
        --index;
        sift_down_max_heap(heap, size, index);
    }
}

static int compare_ints(const void *left, const void *right)
{
    const int a = *(const int *)left;
    const int b = *(const int *)right;

    return (a > b) - (a < b);
}

static int get_n_smallest(const int *data, size_t count, size_t n, int **result)
{
    int *smallest;
    size_t index;

    if (result == NULL || (data == NULL && count != 0U) || n > count) {
        return EINVAL;
    }

    *result = NULL;

    if (n == 0U) {
        return 0;
    }

    if (n > SIZE_MAX / sizeof(*smallest)) {
        return EOVERFLOW;
    }

    smallest = malloc(n * sizeof(*smallest));
    if (smallest == NULL) {
        return ENOMEM;
    }

    for (index = 0U; index < n; ++index) {
        smallest[index] = data[index];
    }

    build_max_heap(smallest, n);

    for (index = n; index < count; ++index) {
        if (data[index] < smallest[0]) {
            smallest[0] = data[index];
            sift_down_max_heap(smallest, n, 0U);
        }
    }

    qsort(smallest, n, sizeof(*smallest), compare_ints);
    *result = smallest;

    return 0;
}

int main(void)
{
    const int data[] = {17, 4, 9, -3, 22, 1, 8, 1, 15};
    const size_t count = sizeof(data) / sizeof(data[0]);
    const size_t n = 4U;
    int *smallest = NULL;
    int status;
    size_t index;

    status = get_n_smallest(data, count, n, &smallest);
    if (status != 0) {
        fprintf(stderr, "get_n_smallest failed: %d\n", status);
        return EXIT_FAILURE;
    }

    for (index = 0U; index < n; ++index) {
        if (printf("%d%s", smallest[index], index + 1U == n ? "\n" : " ") < 0) {
            free(smallest);
            return EXIT_FAILURE;
        }
    }

    free(smallest);
    return EXIT_SUCCESS;
}