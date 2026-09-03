#include <stddef.h>
#include <stdio.h>

size_t count_in_range(const int *list, size_t size, int lower, int upper) {
    size_t count = 0;
    size_t i;

    if (list == NULL) {
        return 0;
    }
    if (lower > upper) {
        return 0;
    }

    for (i = 0; i < size; ++i) {
        if (list[i] >= lower && list[i] <= upper) {
            ++count;
        }
    }

    return count;
}

int main(void) {
    int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    size_t result = count_in_range(values, sizeof(values) / sizeof(values[0]), 3, 7);

    (void)printf("%zu\n", result);

    return 0;
}