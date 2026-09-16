#include <stdio.h>
#include <stdlib.h>

void print_negative_numbers(const int *list, size_t size) {
    if (list == NULL || size == 0) {
        return;
    }

    for (size_t i = 0; i < size; i++) {
        if (list[i] < 0) {
            printf("%d\n", list[i]);
        }
    }
}

int main(void) {
    int numbers[] = {12, -5, 7, -9, 0, 14, -3, 8};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);

    print_negative_numbers(numbers, size);

    return EXIT_SUCCESS;
}