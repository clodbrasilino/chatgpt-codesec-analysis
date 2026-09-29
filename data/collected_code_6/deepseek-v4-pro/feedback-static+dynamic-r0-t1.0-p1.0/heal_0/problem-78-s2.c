#include <stdio.h>
#include <stdlib.h>

int count_odd_set_bits(const int *arr, size_t size) {
    int count = 0;
    
    if (arr == NULL || size == 0) {
        return 0;
    }
    
    for (size_t i = 0; i < size; i++) {
        int value = arr[i];
        int bits_count = 0;
        
        while (value != 0) {
            bits_count += value & 1;
            value >>= 1;
        }
        
        if (bits_count % 2 != 0) {
            count++;
        }
    }
    
    return count;
}

int main(void) {
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);
    
    int result = count_odd_set_bits(numbers, size);
    printf("Count of integers with odd number of set bits: %d\n", result);
    
    return 0;
}