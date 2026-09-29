#include <stdio.h>
#include <stdlib.h>

static int sort_array(int *array, size_t length)
{
    size_t counts[3] = {0U, 0U, 0U};
    size_t index;
    int value;

    if (array == NULL && length != 0U) {
        return -1;
    }

    for (index = 0U; index < length; ++index) {
        value = array[index];
        if (value < 0 || value > 2) {
            return -1;
        }
        ++counts[(size_t)value];
    }

    index = 0U;
    for (value = 0; value <= 2; ++value) {
        size_t count;
        for (count = 0U; count < counts[(size_t)value]; ++count) {
            array[index++] = value;
        }
    }

    return 0;
}

int main(void)
{
    int array[] = {2, 0, 1, 2, 1, 0, 0, 2};
    const size_t length = sizeof(array) / sizeof(array[0]);
    size_t index;

    if (sort_array(array, length) != 0) {
        (void)fprintf(stderr, "Invalid array input\n");
        return EXIT_FAILURE;
    }

    for (index = 0U; index < length; ++index) {
        if (printf("%d%s", array[index],
                   (index + 1U == length) ? "\n" : " ") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}