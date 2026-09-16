#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int element_after_right_rotations(const int *array, size_t length,
                                         size_t index, size_t rotations,
                                         int *result)
{
    size_t original_index;

    if (array == NULL || result == NULL || length == 0U || index >= length) {
        return -1;
    }

    rotations %= length;
    original_index = (index + length - rotations) % length;
    *result = array[original_index];

    return 0;
}

int main(void)
{
    int array[] = {10, 20, 30, 40, 50};
    const size_t length = sizeof(array) / sizeof(array[0]);
    const size_t index = 2U;
    const size_t rotations = 3U;
    int result;

    if (element_after_right_rotations(array, length, index, rotations, &result) != 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", result);
    return EXIT_SUCCESS;
}