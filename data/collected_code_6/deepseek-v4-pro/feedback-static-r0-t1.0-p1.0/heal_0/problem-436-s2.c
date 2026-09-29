#include <stdio.h>
#include <stdlib.h>

void print_negative_numbers(const int *numbers, size_t count) {
    if (numbers == NULL) {
        return;
    }
    
    for (size_t i = 0; i < count; i++) {
        if (numbers[i] < 0) {
            printf("%d ", numbers[i]);
        }
    }
    printf("\n");
}

int main(void) {
    int numbers[] = {5, -3, 10, -8, 0, -2, 7, -15};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    
    print_negative_numbers(numbers, count);
    
    return 0;
}