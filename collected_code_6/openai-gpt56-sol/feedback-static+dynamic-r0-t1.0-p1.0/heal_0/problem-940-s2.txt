#include <stdio.h>
#include <stdlib.h>

static void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

static void heapify(int array[], size_t length, size_t root)
{
    for (;;) {
        size_t largest = root;
        size_t left = root * 2U + 1U;
        size_t right = left + 1U;

        if (left < length && array[left] > array[largest]) {
            largest = left;
        }

        if (right < length && array[right] > array[largest]) {
            largest = right;
        }

        if (largest == root) {
            return;
        }

        swap(&array[root], &array[largest]);
        root = largest;
    }
}

static void heap_sort(int array[], size_t length)
{
    if (array == NULL || length < 2U) {
        return;
    }

    for (size_t i = length / 2U; i > 0U; --i) {
        heapify(array, length, i - 1U);
    }

    for (size_t i = length; i > 1U; --i) {
        swap(&array[0], &array[i - 1U]);
        heapify(array, i - 1U, 0U);
    }
}

int main(void)
{
    int array[] = {12, 11, 13, 5, 6, 7};
    const size_t length = sizeof(array) / sizeof(array[0]);

    heap_sort(array, length);

    for (size_t i = 0U; i < length; ++i) {
        if (printf("%d%s", array[i], i + 1U < length ? " " : "\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}