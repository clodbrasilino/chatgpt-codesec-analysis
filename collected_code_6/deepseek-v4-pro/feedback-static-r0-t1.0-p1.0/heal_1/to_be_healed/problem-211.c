#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/* Possible weaknesses found:
 *  Parameter 'numbers' can be declared as pointer to const [constParameterPointer]
 */
unsigned int count_numbers_with_bits_set(uint32_t *numbers, size_t count, unsigned int oth, unsigned int nth) {
    if (numbers == NULL || oth >= 32 || nth >= 32) {
        return 0;
    }
    
    unsigned int result = 0;
    for (size_t i = 0; i < count; i++) {
        if ((numbers[i] & (1u << oth)) && (numbers[i] & (1u << nth))) {
            result++;
        }
    }
    return result;
}

int main(void) {
    uint32_t numbers[] = {0x0000000F, 0x0000000C, 0x00000003, 0x00000005, 0x0000000A};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    
    unsigned int count_result = count_numbers_with_bits_set(numbers, count, 0, 1);
    printf("%u\n", count_result);
    
    return 0;
}