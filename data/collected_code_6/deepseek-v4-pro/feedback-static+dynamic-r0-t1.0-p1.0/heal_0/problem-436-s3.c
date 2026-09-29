#include <stdio.h>
#include <stdlib.h>

void print_negative_numbers(const int *numbers, size_t size) {
    if (numbers == NULL || size == 0) {
        return;
    }

    for (size_t i = 0; i < size; ++i) {
        if (numbers[i] < 0) {
            printf("%d\n", numbers[i]);
        }
    }
}

int main(void) {
    int numbers[] = {-5, 3, -2, 8, -1, 0, -10, 7};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);

    print_negative_numbers(numbers, size);

    return EXIT_SUCCESS;
}