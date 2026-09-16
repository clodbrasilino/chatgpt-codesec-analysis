#include <stdio.h>
#include <stdlib.h>

void print_odd_numbers(const int *numbers, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        if (numbers[i] % 2 != 0) {
            printf("%d ", numbers[i]);
        }
    }
    printf("\n");
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    print_odd_numbers(numbers, count);
    return 0;
}