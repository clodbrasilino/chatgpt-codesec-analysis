#include <stdio.h>
#include <stdlib.h>

int count_positive_numbers(const int *list, size_t size) {
    if (list == NULL || size == 0) {
        return -1;
    }

    int count = 0;
    for (size_t i = 0; i < size; ++i) {
        if (list[i] > 0) {
            count++;
        }
    }
    return count;
}

int main(void) {
    int numbers[] = {-5, 3, 0, 7, -1, 10, 2};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);

    int positive_count = count_positive_numbers(numbers, size);

    if (positive_count != -1) {
        printf("Number of positive elements: %d\n", positive_count);
    } else {
        printf("Invalid input or empty list.\n");
    }

    return 0;
}