#include <stdio.h>
#include <stdlib.h>

int sum_negative_numbers(const int *numbers, size_t count) {
    int sum = 0;
    
    if (numbers == NULL) {
        return 0;
    }
    
    for (size_t i = 0; i < count; i++) {
        if (numbers[i] < 0) {
            sum += numbers[i];
        }
    }
    
    return sum;
}

int main(void) {
    int numbers[] = {5, -2, 0, -7, 3, -1};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    
    int result = sum_negative_numbers(numbers, count);
    
    printf("%d\n", result);
    
    return 0;
}