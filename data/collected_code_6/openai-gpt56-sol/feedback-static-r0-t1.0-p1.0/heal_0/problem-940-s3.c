#include <stdio.h>
#include <stdlib.h>

static void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

static void sift_down(int array[], size_t root, size_t count)
{
    while (root < count / 2U) {
        size_t child = root * 2U + 1U;

        if (child + 1U < count && array[child] < array[child + 1U]) {
            ++child;
        }

        if (array[root] >= array[child]) {
            break;
        }

        swap(&array[root], &array[child]);
        root = child;
    }
}

static void heap_sort(int array[], size_t count)
{
    if (array == NULL || count < 2U) {
        return;
    }

    for (size_t root = count / 2U; root > 0U; --root) {
        sift_down(array, root - 1U, count);
    }

    for (size_t end = count; end > 1U; --end) {
        swap(&array[0], &array[end - 1U]);
        sift_down(array, 0U, end - 1U);
    }
}

int main(void)
{
    size_t count;

    if (scanf("%zu", &count) != 1) {
        fprintf(stderr, "Failed to read array size.\n");
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(int)) {
        fprintf(stderr, "Array size is too large.\n");
        return EXIT_FAILURE;
    }

    int *array = NULL;

    if (count > 0U) {
        array = malloc(count * sizeof(*array));
        if (array == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0U; i < count; ++i) {
        if (scanf("%d", &array[i]) != 1) {
            fprintf(stderr, "Failed to read array element.\n");
            free(array);
            return EXIT_FAILURE;
        }
    }

    heap_sort(array, count);

    for (size_t i = 0U; i < count; ++i) {
        if (printf("%d%s", array[i], i + 1U < count ? " " : "\n") < 0) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    free(array);
    return EXIT_SUCCESS;
}