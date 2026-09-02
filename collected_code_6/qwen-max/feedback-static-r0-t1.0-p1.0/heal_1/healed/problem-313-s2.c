#include <stdio.h>

void print_positive(const int *numbers, int size) {
    for (int i = 0; i < size; ++i) {
        if (numbers[i] > 0) {
            printf("%d ", numbers[i]);
        }
    }
    printf("\n");
}

int main() {
    int numbers[] = {1, -3, 4, -5, 6, 0, -2, 8};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    print_positive(numbers, size);
    return 0;
}