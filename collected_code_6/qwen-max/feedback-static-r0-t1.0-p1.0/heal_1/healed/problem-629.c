#include <stdio.h>
#include <stdlib.h>

void find_even_numbers(const int *numbers, int length) {
    for (int i = 0; i < length; ++i) {
        if (numbers[i] % 2 == 0) {
            printf("%d ", numbers[i]);
        }
    }
    printf("\n");
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int length = sizeof(numbers) / sizeof(numbers[0]);

    find_even_numbers(numbers, length);

    return 0;
}