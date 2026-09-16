#include <stdio.h>
#include <stddef.h>

static int find_extra_index(const int larger[], size_t larger_len,
                            const int smaller[], size_t smaller_len,
                            size_t *index)
{
    size_t left = 0;
    size_t right;

    if (larger == NULL || smaller == NULL || index == NULL ||
        larger_len == 0 || smaller_len + 1 != larger_len) {
        return 0;
    }

    right = smaller_len;

    while (left < right) {
        size_t mid = left + (right - left) / 2;

        if (larger[mid] == smaller[mid]) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    *index = left;
    return 1;
}

int main(void)
{
    const int larger[] = {2, 4, 6, 8, 9, 10, 12};
    const int smaller[] = {2, 4, 6, 8, 10, 12};
    const size_t larger_len = sizeof(larger) / sizeof(larger[0]);
    const size_t smaller_len = sizeof(smaller) / sizeof(smaller[0]);
    size_t index;

    if (!find_extra_index(larger, larger_len, smaller, smaller_len, &index)) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (printf("%zu\n", index) < 0) {
        return 1;
    }

    return 0;
}