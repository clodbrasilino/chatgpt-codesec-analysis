#include <stdio.h>
#include <stdlib.h>

void print_positive_numbers(int *numbers, int size) {
    for (int i = 0; i < size; ++i) {
        if (numbers[i] > 0) {
            printf("%d\n", numbers[i]);
        }
    }
}

int main() {
    int numbers[] = { -1, 2, -3, 4, 5, -6 };
    int size = sizeof(numbers) / sizeof(numbers[0]);

    print_positive_numbers(numbers, size);

    return 0;
}