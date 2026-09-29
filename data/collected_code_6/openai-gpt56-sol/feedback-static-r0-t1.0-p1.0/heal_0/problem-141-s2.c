#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

static void reverse_prefix(int *array, size_t end)
{
    size_t start = 0;

    while (start < end) {
        int temporary = array[start];
        array[start] = array[end];
        array[end] = temporary;
        ++start;
        --end;
    }
}

static size_t find_max_index(const int *array, size_t length)
{
    size_t max_index = 0;

    for (size_t i = 1; i < length; ++i) {
        if (array[i] > array[max_index]) {
            max_index = i;
        }
    }

    return max_index;
}

static void pancake_sort(int *array, size_t length)
{
    for (size_t current = length; current > 1; --current) {
        size_t max_index = find_max_index(array, current);

        if (max_index == current - 1) {
            continue;
        }

        if (max_index != 0) {
            reverse_prefix(array, max_index);
        }

        reverse_prefix(array, current - 1);
    }
}

static int read_size(size_t *length)
{
    unsigned long long input_length;

    if (scanf("%llu", &input_length) != 1) {
        return 0;
    }

    if (input_length > SIZE_MAX / sizeof(int)) {
        return 0;
    }

    *length = (size_t)input_length;
    return 1;
}

int main(void)
{
    size_t length;

    if (!read_size(&length)) {
        fputs("Invalid list size.\n", stderr);
        return EXIT_FAILURE;
    }

    int *array = NULL;

    if (length > 0) {
        array = malloc(length * sizeof(*array));
        if (array == NULL) {
            fputs("Memory allocation failed.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < length; ++i) {
        if (scanf("%d", &array[i]) != 1) {
            fputs("Invalid list element.\n", stderr);
            free(array);
            return EXIT_FAILURE;
        }
    }

    pancake_sort(array, length);

    for (size_t i = 0; i < length; ++i) {
        if (i > 0 && putchar(' ') == EOF) {
            free(array);
            return EXIT_FAILURE;
        }

        if (printf("%d", array[i]) < 0) {
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