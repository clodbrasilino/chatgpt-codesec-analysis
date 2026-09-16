#include <stdio.h>
#include <limits.h>
#include <stddef.h>

int find_smallest(const int *list, size_t size) {
    int smallest;

    if (list == NULL || size == 0) {
        return INT_MIN;
    }

    smallest = list[0];

    for (size_t i = 1; i < size; ++i) {
        if (list[i] < smallest) {
            smallest = list[i];
        }
    }

    return smallest;
}

int main(void) {
    int numbers[] = {5, 2, 9, 1, 7};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);

    int result = find_smallest(numbers, count);

    printf("%d\n", result);

    return 0;
}