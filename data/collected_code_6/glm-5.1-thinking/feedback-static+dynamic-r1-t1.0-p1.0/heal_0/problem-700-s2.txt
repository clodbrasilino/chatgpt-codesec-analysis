#include <stdio.h>
#include <stddef.h>

size_t count_in_range(const int *arr, size_t size, int min, int max) {
    if (arr == NULL || size == 0 || min > max) {
        return 0;
    }

    size_t count = 0;
    for (size_t i = 0; i < size; i++) {
        if (arr[i] >= min && arr[i] <= max) {
            count++;
        }
    }
    return count;
}

int main(void) {
    int data[] = {1, 5, 10, 15, 20, 25, 30};
    size_t n = sizeof(data) / sizeof(data[0]);
    int lower = 10;
    int upper = 25;

    size_t result = count_in_range(data, n, lower, upper);
    printf("%zu\n", result);

    return 0;
}