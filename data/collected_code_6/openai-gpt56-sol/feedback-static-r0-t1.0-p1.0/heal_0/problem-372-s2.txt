#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static void swap_int(int *a, int *b)
{
    int temporary = *a;
    *a = *b;
    *b = temporary;
}

static void sift_down(int elements[], size_t root, size_t count)
{
    while (root <= (count - 2U) / 2U) {
        size_t child = root * 2U + 1U;

        if (child + 1U < count && elements[child] < elements[child + 1U]) {
            ++child;
        }

        if (elements[root] >= elements[child]) {
            break;
        }

        swap_int(&elements[root], &elements[child]);
        root = child;
    }
}

static void heap_sort(int elements[], size_t count)
{
    if (elements == NULL || count < 2U) {
        return;
    }

    for (size_t index = count / 2U; index > 0U; --index) {
        sift_down(elements, index - 1U, count);
    }

    for (size_t remaining = count; remaining > 1U; --remaining) {
        swap_int(&elements[0], &elements[remaining - 1U]);
        sift_down(elements, 0U, remaining - 1U);
    }
}

int main(void)
{
    size_t count;

    if (scanf("%zu", &count) != 1) {
        fputs("Invalid element count\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(int)) {
        fputs("Element count is too large\n", stderr);
        return EXIT_FAILURE;
    }

    int *elements = NULL;

    if (count > 0U) {
        elements = malloc(count * sizeof(*elements));
        if (elements == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t index = 0U; index < count; ++index) {
        if (scanf("%d", &elements[index]) != 1) {
            fputs("Invalid element\n", stderr);
            free(elements);
            return EXIT_FAILURE;
        }
    }

    heap_sort(elements, count);

    for (size_t index = 0U; index < count; ++index) {
        if (printf("%s%d", index == 0U ? "" : " ", elements[index]) < 0) {
            free(elements);
            return EXIT_FAILURE;
        }
    }

    if (putchar('\n') == EOF) {
        free(elements);
        return EXIT_FAILURE;
    }

    free(elements);
    return EXIT_SUCCESS;
}