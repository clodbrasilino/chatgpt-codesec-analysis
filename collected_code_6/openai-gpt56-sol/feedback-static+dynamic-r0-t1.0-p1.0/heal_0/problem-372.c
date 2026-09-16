#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

static void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

static void sift_down(int array[], size_t count, size_t root)
{
    for (;;) {
        size_t largest = root;
        size_t left;
        size_t right;

        if (root > (SIZE_MAX - 1U) / 2U) {
            return;
        }

        left = (2U * root) + 1U;
        if (left >= count) {
            return;
        }

        right = left + 1U;

        if (array[left] > array[largest]) {
            largest = left;
        }

        if (right < count && array[right] > array[largest]) {
            largest = right;
        }

        if (largest == root) {
            return;
        }

        swap(&array[root], &array[largest]);
        root = largest;
    }
}

static void heap_sort(int array[], size_t count)
{
    size_t i;

    if (array == NULL || count < 2U) {
        return;
    }

    for (i = count / 2U; i > 0U; --i) {
        sift_down(array, count, i - 1U);
    }

    for (i = count; i > 1U; --i) {
        swap(&array[0], &array[i - 1U]);
        sift_down(array, i - 1U, 0U);
    }
}

int main(void)
{
    int *array = NULL;
    size_t count;
    size_t i;

    if (scanf("%zu", &count) != 1) {
        fputs("Failed to read the element count.\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*array)) {
        fputs("The requested allocation is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > 0U) {
        array = malloc(count * sizeof(*array));
        if (array == NULL) {
            fprintf(stderr, "Memory allocation failed: errno=%d\n", errno);
            return EXIT_FAILURE;
        }
    }

    for (i = 0U; i < count; ++i) {
        if (scanf("%d", &array[i]) != 1) {
            fputs("Failed to read an element.\n", stderr);
            free(array);
            return EXIT_FAILURE;
        }
    }

    heap_sort(array, count);

    for (i = 0U; i < count; ++i) {
        if (printf("%d%s", array[i], (i + 1U < count) ? " " : "\n") < 0) {
            fputs("Failed to write output.\n", stderr);
            free(array);
            return EXIT_FAILURE;
        }
    }

    free(array);
    return EXIT_SUCCESS;
}