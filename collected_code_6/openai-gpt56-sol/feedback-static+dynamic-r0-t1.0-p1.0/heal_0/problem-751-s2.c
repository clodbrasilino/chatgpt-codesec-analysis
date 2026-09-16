#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static bool is_min_heap(const int array[], size_t length)
{
    if (array == NULL && length != 0U) {
        return false;
    }

    for (size_t child = 1U; child < length; ++child) {
        size_t parent = (child - 1U) / 2U;

        if (array[parent] > array[child]) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    int array[] = {1, 3, 2, 7, 6, 4, 5};
    size_t length = sizeof(array) / sizeof(array[0]);

    if (printf("%s\n", is_min_heap(array, length) ? "Min heap" : "Not a min heap") < 0) {
        return 1;
    }

    return 0;
}