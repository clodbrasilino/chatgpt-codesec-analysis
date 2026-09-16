#include <stdio.h>
#include <stddef.h>

size_t count_in_range(const int *list, size_t size, int min_val, int max_val) {
    if (list == NULL || size == 0) {
        return 0;
    }
    if (min_val > max_val) {
        return 0;
    }

    size_t count = 0;
    for (size_t i = 0; i < size; i++) {
        if (list[i] >= min_val && list[i] <= max_val) {
            count++;
        }
    }
    return count;
}

int main(void) {
    int data[] = {1, 5, 10, 15, 20, 25, 30};
    size_t data_size = sizeof(data) / sizeof(data[0]);
    int min_range = 10;
    int max_range = 25;

    size_t result = count_in_range(data, data_size, min_range, max_range);
    printf("%zu\n", result);

    return 0;
}