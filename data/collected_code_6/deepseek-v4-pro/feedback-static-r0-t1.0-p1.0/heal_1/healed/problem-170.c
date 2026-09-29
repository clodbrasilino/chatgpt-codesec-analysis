#include <stdio.h>
#include <stdlib.h>

int sum_in_range(const int *list, int size, int start, int end) {
    if (list == NULL || size <= 0) {
        return 0;
    }
    if (start < 0) {
        start = 0;
    }
    if (end >= size) {
        end = size - 1;
    }
    if (start > end) {
        return 0;
    }
    int sum = 0;
    for (int i = start; i <= end; i++) {
        sum += list[i];
    }
    return sum;
}

int main(void) {
    int list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(list) / sizeof(list[0]);

    int result = sum_in_range(list, size, 2, 5);
    printf("Sum: %d\n", result);

    result = sum_in_range(list, size, -3, 4);
    printf("Sum with negative start: %d\n", result);

    result = sum_in_range(list, size, 8, 20);
    printf("Sum with large end: %d\n", result);

    result = sum_in_range(list, size, 5, 2);
    printf("Sum with invalid range: %d\n", result);

    result = sum_in_range(NULL, size, 0, 5);
    printf("Sum with NULL list: %d\n", result);

    return 0;
}