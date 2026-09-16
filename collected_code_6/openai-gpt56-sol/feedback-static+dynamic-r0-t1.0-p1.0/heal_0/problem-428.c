#include <stdio.h>
#include <stdlib.h>

static void shell_sort(int *array, size_t length)
{
    for (size_t gap = length / 2U; gap > 0U; gap /= 2U) {
        for (size_t i = gap; i < length; ++i) {
            int value = array[i];
            size_t j = i;

            while (j >= gap && array[j - gap] > value) {
                array[j] = array[j - gap];
                j -= gap;
            }

            array[j] = value;
        }
    }
}

int main(void)
{
    int array[] = {23, 12, 1, 8, 34, 54, 2, 3};
    const size_t length = sizeof(array) / sizeof(array[0]);

    shell_sort(array, length);

    for (size_t i = 0U; i < length; ++i) {
        if (printf("%d%s", array[i], (i + 1U < length) ? " " : "\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}