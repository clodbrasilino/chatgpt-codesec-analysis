#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

unsigned int count_set_bits(uint32_t number) {
    unsigned int count = 0;
    while (number != 0) {
        number &= (number - 1);
        count++;
    }
    return count;
}

int main(void) {
    uint32_t input;
    int scan_result;
    
    printf("Enter a number: ");
    scan_result = scanf("%" SCNu32, &input);
    
    if (scan_result != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    printf("Number of set bits: %u\n", count_set_bits(input));
    
    return 0;
}