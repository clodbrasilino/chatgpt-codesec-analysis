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

static size_t find_max_index(const int *array, size_t length)
{
    size_t max_index = 0;

    for (size_t index = 1; index < length; ++index) {
        if (array[index] > array[max_index]) {
            max_index = index;
        }
    }

    return max_index;
}

static void pancake_sort(int *array, size_t length)
{
    if (array == NULL || length < 2) {
        return;
    }

    for (size_t current_length = length; current_length > 1; --current_length) {
        size_t max_index = find_max_index(array, current_length);

        if (max_index == current_length - 1) {
            continue;
        }

        if (max_index > 0) {
            reverse_prefix(array, max_index + 1);
        }

        reverse_prefix(array, current_length);
    }
}

int main(void)
{
    int values[] = {23, 10, 20, 11, 12, 6, 7};
    size_t count = sizeof(values) / sizeof(values[0]);

    pancake_sort(values, count);

    for (size_t index = 0; index < count; ++index) {
        if (printf("%s%d", index == 0 ? "" : " ", values[index]) < 0) {
            return EXIT_FAILURE;
        }
    }

    if (putchar('\n') == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}