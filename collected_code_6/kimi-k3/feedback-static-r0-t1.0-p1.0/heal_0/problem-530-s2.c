#include <stdio.h>
#include <stdlib.h>

float ratio_of_negatives(const int *array, size_t size) {
    if (array == NULL || size == 0) {
        return 0.0f;
    }

    size_t negative_count = 0;
    for (size_t i = 0; i < size; ++i) {
        if (array[i] < 0) {
            ++negative_count;
        }
    }

    return (float)negative_count / (float)size;
}

int main(void) {
    int numbers[] = {1, -2, 3, -4, 5, -6, 7, -8, 9, -10};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);

    float ratio = ratio_of_negatives(numbers, size);
    printf("Ratio of negative numbers: %.2f\n", ratio);

    return EXIT_SUCCESS;
}