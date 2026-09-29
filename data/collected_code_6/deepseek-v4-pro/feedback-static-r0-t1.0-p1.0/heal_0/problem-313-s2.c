#include <stdio.h>
#include <stdlib.h>

void print_positive_numbers(const int *numbers, size_t count) {
    for (size_t i = 0; i < count; i++) {
        if (numbers[i] > 0) {
            printf("%d\n", numbers[i]);
        }
    }
}

int main(void) {
    int numbers[] = {-5, 3, -1, 7, 0, 10, -3, 2};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);

    print_positive_numbers(numbers, count);

    return 0;
}