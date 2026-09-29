#include <stdio.h>
#include <stdlib.h>

static int sort_array(int *array, size_t length)
{
    size_t counts[3] = {0U, 0U, 0U};
    size_t index = 0U;

    if (array == NULL && length != 0U) {
        return -1;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (array[i] < 0 || array[i] > 2) {
            return -1;
        }
        ++counts[(size_t)array[i]];
    }

    for (size_t value = 0U; value < 3U; ++value) {
        for (size_t count = 0U; count < counts[value]; ++count) {
            array[index++] = (int)value;
        }
    }

    return 0;
}

int main(void)
{
    int array[] = {2, 0, 1, 2, 1, 0, 2, 0, 1};
    const size_t length = sizeof(array) / sizeof(array[0]);

    if (sort_array(array, length) != 0) {
        (void)fprintf(stderr, "Invalid array input.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (printf("%d%s", array[i], i + 1U == length ? "\n" : " ") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}