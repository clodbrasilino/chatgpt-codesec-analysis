#include <stdio.h>

void print_negative_numbers(const int numbers[], int size) {
    if (numbers == NULL || size <= 0) {
        return;
    }
    
    for (int i = 0; i < size; i++) {
        if (numbers[i] < 0) {
            printf("%d\n", numbers[i]);
        }
    }
}

int main(void) {
    int numbers[] = {5, -3, 8, -1, 0, -7, 12, -4};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    print_negative_numbers(numbers, size);
    
    return 0;
}