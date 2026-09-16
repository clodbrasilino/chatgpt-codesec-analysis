#include <stdio.h>
#include <stdlib.h>

static void swap(int *a, int *b)
{
    int temporary = *a;
    *a = *b;
    *b = temporary;
}

static void sift_down(int array[], size_t length, size_t root)
{
    for (;;) {
        size_t largest = root;
        size_t left;
        size_t right;

        if (root > (length - 1U) / 2U) {
            break;
        }

        left = (root * 2U) + 1U;
        right = left + 1U;

        if (left < length && array[left] > array[largest]) {
            largest = left;
        }

        if (right < length && array[right] > array[largest]) {
            largest = right;
        }

        if (largest == root) {
            break;
        }

        swap(&array[root], &array[largest]);
        root = largest;
    }
}

static void heap_sort(int array[], size_t length)
{
    size_t index;

    if (array == NULL || length < 2U) {
        return;
    }

    for (index = length / 2U; index > 0U; --index) {
        sift_down(array, length, index - 1U);
    }

    for (index = length; index > 1U; --index) {
        swap(&array[0], &array[index - 1U]);
        sift_down(array, index - 1U, 0U);
    }
}

int main(void)
{
    int array[] = {12, 11, 13, 5, 6, 7};
    size_t length = sizeof(array) / sizeof(array[0]);
    size_t index;

    heap_sort(array, length);

    for (index = 0U; index < length; ++index) {
        if (printf("%d%s", array[index], index + 1U < length ? " " : "\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}