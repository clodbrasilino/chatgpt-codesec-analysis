#include <stdio.h>
#include <stdlib.h>

static void reverse_prefix(int *array, size_t length)
{
    size_t left = 0;
    size_t right = length - 1;

    while (left < right) {
        int temporary = array[left];
        array[left] = array[right];
        array[right] = temporary;
        ++left;
        --right;
    }
}

static size_t find_maximum_index(const int *array, size_t length)
{
    size_t maximum_index = 0;

    for (size_t i = 1; i < length; ++i) {
        if (array[i] > array[maximum_index]) {
            maximum_index = i;
        }
    }

    return maximum_index;
}

static void pancake_sort(int *array, size_t length)
{
    if (array == NULL || length < 2) {
        return;
    }

    for (size_t current_length = length; current_length > 1; --current_length) {
        size_t maximum_index = find_maximum_index(array, current_length);

        if (maximum_index == current_length - 1) {
            continue;
        }

        if (maximum_index > 0) {
            reverse_prefix(array, maximum_index + 1);
        }

        reverse_prefix(array, current_length);
    }
}

int main(void)
{
    int values[] = {23, 10, 20, 11, 12, 6, 7};
    const size_t count = sizeof(values) / sizeof(values[0]);

    pancake_sort(values, count);

    for (size_t i = 0; i < count; ++i) {
        if (printf("%d%s", values[i], i + 1 < count ? " " : "\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}