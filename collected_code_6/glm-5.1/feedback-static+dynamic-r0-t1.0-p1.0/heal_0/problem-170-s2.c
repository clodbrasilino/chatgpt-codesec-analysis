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
        start = size - 1;
    }

    if (end >= size) {
        end = size - 1;
    }

    if (start > end) {
        size_t temp = start;
        start = end;
        end = temp;
    }

    int sum = 0;
    for (size_t i = start; i <= end; i++) {
        sum += list[i];
    }

    return sum;
}

int main(void) {
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t data_size = sizeof(data) / sizeof(data[0]);

    int result1 = sum_range(data, data_size, 2, 5);
    printf("%d\n", result1);

    int result2 = sum_range(data, data_size, 5, 2);
    printf("%d\n", result2);

    int result3 = sum_range(data, data_size, 8, 15);
    printf("%d\n", result3);

    int result4 = sum_range(NULL, data_size, 0, 5);
    printf("%d\n", result4);

    return 0;
}