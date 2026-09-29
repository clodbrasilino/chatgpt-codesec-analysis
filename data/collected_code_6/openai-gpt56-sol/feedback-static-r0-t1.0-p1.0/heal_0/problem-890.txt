#include <stdio.h>
#include <stddef.h>

static int find_extra_index(const int longer[], size_t longer_size,
                            const int shorter[], size_t shorter_size,
                            size_t *index)
{
    if (longer == NULL || shorter == NULL || index == NULL ||
        longer_size != shorter_size + 1U) {
        return 0;
    }

    size_t left = 0U;
    size_t right = shorter_size;

    while (left < right) {
        const size_t middle = left + (right - left) / 2U;

        if (longer[middle] == shorter[middle]) {
            left = middle + 1U;
        } else {
            right = middle;
        }
    }

    for (size_t i = 0U; i < left; ++i) {
        if (longer[i] != shorter[i]) {
            return 0;
        }
    }

    for (size_t i = left; i < shorter_size; ++i) {
        if (longer[i + 1U] != shorter[i]) {
            return 0;
        }
    }

    *index = left;
    return 1;
}

int main(void)
{
    const int longer[] = {1, 2, 3, 4, 5, 6};
    const int shorter[] = {1, 2, 3, 5, 6};
    const size_t longer_size = sizeof longer / sizeof longer[0];
    const size_t shorter_size = sizeof shorter / sizeof shorter[0];
    size_t index = 0U;

    if (!find_extra_index(longer, longer_size, shorter, shorter_size, &index)) {
        (void)fprintf(stderr, "Unable to find a unique extra element.\n");
        return 1;
    }

    if (printf("%zu\n", index) < 0) {
        return 1;
    }

    return 0;
}