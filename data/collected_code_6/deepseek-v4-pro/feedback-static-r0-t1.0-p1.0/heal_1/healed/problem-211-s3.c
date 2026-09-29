#include <stdio.h>
#include <stdlib.h>

int count_numbers_with_bits_set(const int *numbers, int size, int n) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if ((numbers[i] & 1) && (numbers[i] & (1 << n))) {
            count++;
        }
    }
    return count;
}

int main(void) {
    int numbers[] = {3, 5, 7, 11, 13};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    int n = 1;
    
    int result = count_numbers_with_bits_set(numbers, size, n);
    printf("Count: %d\n", result);
    
    return 0;
}