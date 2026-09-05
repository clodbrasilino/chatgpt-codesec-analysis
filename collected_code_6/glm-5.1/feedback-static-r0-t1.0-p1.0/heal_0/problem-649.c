#include <stdio.h>
#include <stdlib.h>

int sum_range(const int *list, size_t size, size_t start, size_t end) {
    if (list == NULL) {
        return 0;
    }

    if (size == 0) {
        return 0;
    }

    if (start >= size) {
        return 0;
    }

    if (end >= size) {
        end = size - 1;
    }

    if (start > end) {
        return 0;
    }

    int sum = 0;
    for (size_t i = start; i <= end; ++i) {
        sum += list[i];
    }

    return sum;
}

int main(void) {
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t data_size = sizeof(data) / sizeof(data[0]);

    size_t start_index = 2;
    size_t end_index = 6;

    int result = sum_range(data, data_size, start_index, end_index);

    printf("%d\n", result);

    return 0;
}