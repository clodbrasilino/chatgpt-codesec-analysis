#include <stdio.h>

void print_negative_numbers(int *numbers, int length) {
    for (int i = 0; i < length; ++i) {
        if (numbers[i] < 0) {
            printf("%d\n", numbers[i]);
        }
    }
}

int main() {
    int numbers[] = {3, -1, -4, 2, 0, -6, 8};
    int length = sizeof(numbers) / sizeof(numbers[0]);
    print_negative_numbers(numbers, length);
    return 0;
}