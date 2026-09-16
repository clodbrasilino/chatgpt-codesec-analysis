#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>

static int find_equilibrium_index(const int *array, size_t length, size_t *index)
{
    if (array == NULL || index == NULL || length == 0U) {
        return 0;
    }

    int64_t right_sum = 0;
    int64_t left_sum = 0;

    for (size_t i = 0U; i < length; ++i) {
        right_sum += (int64_t)array[i];
    }

    for (size_t i = 0U; i < length; ++i) {
        right_sum -= (int64_t)array[i];

        if (left_sum == right_sum) {
            *index = i;
            return 1;
        }

        left_sum += (int64_t)array[i];
    }

    return 0;
}

int main(void)
{
    int array[] = {-7, 1, 5, 2, -4, 3, 0};
    const size_t length = sizeof(array) / sizeof(array[0]);
    size_t index = 0U;

    if (find_equilibrium_index(array, length, &index) != 0) {
        if (printf("%zu\n", index) < 0) {
            return 1;
        }
    } else {
        if (printf("No equilibrium index\n") < 0) {
            return 1;
        }
    }

    return 0;
}