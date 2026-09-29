#include <stdio.h>
#include <stddef.h>

static int find_fixed_point(const int array[], size_t length, size_t *index)
{
    if (array == NULL || index == NULL) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        if (array[i] >= 0 && (size_t)array[i] == i) {
            *index = i;
            return 1;
        }
    }

    return 0;
}

int main(void)
{
    const int array[] = {-10, -5, 0, 3, 7};
    const size_t length = sizeof(array) / sizeof(array[0]);
    size_t index = 0;

    if (find_fixed_point(array, length, &index)) {
        if (printf("Fixed point: %zu\n", index) < 0) {
            return 1;
        }
    } else {
        if (printf("No fixed point found.\n") < 0) {
            return 1;
        }
    }

    return 0;
}