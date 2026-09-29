#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

static int find_equilibrium_index(const int *array, size_t length, size_t *index)
{
    int64_t right_sum = 0;
    int64_t left_sum = 0;

    if (array == NULL || index == NULL || length == 0) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        right_sum += (int64_t)array[i];
    }

    for (size_t i = 0; i < length; ++i) {
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
    const int array[] = {-7, 1, 5, 2, -4, 3, 0};
    const size_t length = sizeof array / sizeof array[0];
    size_t equilibrium_index = 0;

    if (find_equilibrium_index(array, length, &equilibrium_index)) {
        if (printf("%zu\n", equilibrium_index) < 0) {
            return 1;
        }
    } else {
        if (printf("No equilibrium index\n") < 0) {
            return 1;
        }
    }

    return 0;
}