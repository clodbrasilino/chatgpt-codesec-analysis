#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static void swap_ints(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

static void sift_down(int *array, size_t count, size_t root)
{
    while (root < count / 2U) {
        size_t child = root * 2U + 1U;

        if (child + 1U < count && array[child] < array[child + 1U]) {
            ++child;
        }

        if (array[root] >= array[child]) {
            break;
        }

        swap_ints(&array[root], &array[child]);
        root = child;
    }
}

static int heap_sort(int *array, size_t count)
{
    size_t i;

    if (array == NULL && count != 0U) {
        return -1;
    }

    if (count < 2U) {
        return 0;
    }

    for (i = count / 2U; i > 0U; --i) {
        sift_down(array, count, i - 1U);
    }

    for (i = count; i > 1U; --i) {
        swap_ints(&array[0], &array[i - 1U]);
        sift_down(array, i - 1U, 0U);
    }

    return 0;
}

int main(void)
{
    size_t count;
    size_t i;
    int *array = NULL;

    if (scanf("%zu", &count) != 1) {
        fputs("Invalid element count\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*array)) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > 0U) {
        array = malloc(count * sizeof(*array));
        if (array == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (i = 0U; i < count; ++i) {
        if (scanf("%d", &array[i]) != 1) {
            fputs("Invalid element\n", stderr);
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (heap_sort(array, count) != 0) {
        fputs("Unable to sort elements\n", stderr);
        free(array);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < count; ++i) {
        if (printf("%s%d", i == 0U ? "" : " ", array[i]) < 0) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (putchar('\n') == EOF) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);
    return EXIT_SUCCESS;
}