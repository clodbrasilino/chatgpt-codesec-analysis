#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static bool is_min_heap(const int array[], size_t length)
{
    if (array == NULL) {
        return length == 0U;
    }

    for (size_t parent = 0U; parent < length / 2U; ++parent) {
        size_t left = parent * 2U + 1U;
        size_t right = left + 1U;

        if (array[parent] > array[left]) {
            return false;
        }

        if (right < length && array[parent] > array[right]) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    const int array[] = {1, 3, 2, 7, 6, 4, 5};
    const size_t length = sizeof(array) / sizeof(array[0]);

    if (is_min_heap(array, length)) {
        puts("The array represents a min heap.");
    } else {
        puts("The array does not represent a min heap.");
    }

    return 0;
}