#include <stdio.h>
#include <stddef.h>

size_t count_in_range(const int *list, size_t size, int lower, int upper) {
    if (list == NULL || lower > upper) {
        return 0;
    }

    size_t count = 0;
    for (size_t i = 0; i < size; ++i) {
        if (list[i] >= lower && list[i] <= upper) {
            ++count;
        }
    }
    return count;
}

int main(void) {
    int values[] = {1, 5, 10, 15, 20, 25};
    size_t size = sizeof(values) / sizeof(values[0]);
    size_t result = count_in_range(values, size, 5, 20);
    printf("%zu\n", result);
    return 0;
}